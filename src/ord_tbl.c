/**
 * ord_tbl.c - Implements a system for drawing objects in order of depth
 *
 * userWork->entries is an array of OrdTblNodes that also form a linked list
 * with userWork->firstEntry as a pointer to the first node of the list. The
 * nodes in userWork->entries don't actually draw anything, but serve as
 * places where other nodes (that do draw objects) can be inserted. Using this as
 * an array allows for quick O(1) lookup, since an appropriate spot to insert a
 * new node can be found by simply computing the depth of the object's position
 * in view space, and using that value to index into the array.
 */
#include <stddef.h>
#include <dolphin.h>

#include "global.h"
#include "mathutil.h"
#include "ord_tbl.h"

u8 lbl_80292E70[0x20000];

static void clear_ord_table(struct OrdTblNode *ordTbl, int count, u32 order);
static void draw_nodes(struct OrdTblNode *node);
static void reset_alloc_info(void);

/* Initializes parameters for the ordering table. Called at game startup */
void ord_tbl_init(float depthOffset, float minDepth, float maxDepth, void *buffer, int maxEntries)
{
    userWork->entries = buffer;
    userWork->maxEntries = maxEntries;
    userWork->depthOffset = depthOffset;
    userWork->minDepth = minDepth;
    userWork->maxDepth = maxDepth;
    userWork->depthRange = maxDepth - minDepth;
    ord_tbl_reset();
}

/* Resets the ordering table state. Called at the start of each frame */
void ord_tbl_reset(void)
{
    clear_ord_table(userWork->entries, userWork->maxEntries, 1);
    userWork->lastEntry = &userWork->entries[userWork->maxEntries - 1];
    userWork->firstEntry = &userWork->entries[0];
}

void ord_tbl_set_depth_offset(float offset)
{
    userWork->depthOffset = offset;
}

void ord_tbl_add_depth_offset(float offset)
{
    userWork->depthOffset += offset;
}

/* Returns the entry in the ordering table based on the depth of 'pos' in view
 * space. Before calling this function, mathutilData->mtxA must be initialized
 * with a matrix that converts 'pos' to view space. */
struct OrdTblNode *ord_tbl_get_entry_for_pos(Point3d *pos)
{
    Point3d pos_rt_view;
    float minDepth;
    float depth;
    int index;
    struct OrdTblNode *entry;

    // Convert the point into view space coordinates
    mathutil_mtxA_tf_point(pos, &pos_rt_view);
    minDepth = userWork->minDepth;
    pos_rt_view.z = -pos_rt_view.z;
    if (pos_rt_view.z < minDepth)
        pos_rt_view.z = minDepth;
    depth = mathutil_vec_len(&pos_rt_view) + userWork->depthOffset - minDepth;

    // Convert the depth to an index into the table
    if (depth < 0.0f)
        index = 0;
    else
    {
        index = userWork->maxEntries * depth / (depth + userWork->depthRange);
        if (index >= userWork->maxEntries)
            index = userWork->maxEntries - 1;
    }

    entry = &userWork->entries[index];
    if (userWork->lastEntry > entry)
        userWork->lastEntry = entry;
    if (userWork->firstEntry < entry)
        userWork->firstEntry = entry;
    return entry;
}

/* Similar to 'ord_tbl_get_entry_for_pos', but with an additional parameter that
 * is added to the computed index. */
struct OrdTblNode *ord_tbl_get_entry_for_pos_offset_index(Point3d *pos, int indexOffset)
{
    Point3d pos_rt_view;
    float minDepth;
    float depth;
    int index;
    struct OrdTblNode *entry;

    // Convert the point into view space coordinates
    mathutil_mtxA_tf_point(pos, &pos_rt_view);
    minDepth = userWork->minDepth;
    pos_rt_view.z = -pos_rt_view.z;
    if (pos_rt_view.z < minDepth)
        pos_rt_view.z = minDepth;
    depth = mathutil_vec_len(&pos_rt_view) + userWork->depthOffset - minDepth;

    // Convert the depth to an index into the table
    if (depth < 0.0f)
        index = 0;
    else
    {
        index = userWork->maxEntries * depth / (depth + userWork->depthRange);
        index = indexOffset + index;
        if (index < 0)
            index = 0;
        else if (index >= userWork->maxEntries)
            index = userWork->maxEntries - 1;
    }

    entry = &userWork->entries[index];
    if (userWork->lastEntry > entry)
        userWork->lastEntry = entry;
    if (userWork->firstEntry < entry)
        userWork->firstEntry = entry;
    return entry;
}

/* Draws all nodes in the ordering table. Called at the end of each frame. */
void ord_tbl_draw_nodes(void)
{
    if (userWork->firstEntry >= userWork->lastEntry)
    {
        if (userWork->lastEntry > &userWork->entries[0])
            userWork->lastEntry[-1].next = NULL;  // Make sure the list is terminated
        draw_nodes(userWork->firstEntry);
    }
    ord_tbl_reset();
}

/* Clears all nodes in the table and links them in order */
static void clear_ord_table(struct OrdTblNode *ordTbl, int count, u32 order)
{
    int i;
    struct OrdTblNode *node;

    if (order == 0)
    {
        // first to last (not actually used)
        node = ordTbl;
        for (i = count - 1; i > 0; i--)
        {
            node->next = node + 1;
            node->drawFunc = NULL;
            node++;
        }
        node->next = NULL;
        node->drawFunc = NULL;
    }
    else
    {
        // last to first
        node = &ordTbl[count - 1];
        for (i = count - 1; i > 0; i--)
        {
            node->next = node - 1;
            node->drawFunc = NULL;
            node--;
        }
        node->next = NULL;
        node->drawFunc = NULL;
    }
    reset_alloc_info();
}

/* Calls the draw callback of all nodes in the list starting at 'node' */
static void draw_nodes(struct OrdTblNode *node)
{
    while (node != NULL)
    {
        if (node->drawFunc != NULL)
            node->drawFunc(node);
        node = node->next;
    }
}

static struct
{
    u8 *currPtr;
    u8 *initPtr;
    u32 initSize;
    u32 currSize;
} ordTblAllocInfo;

/* Resets the ptr and size to that initially set by ord_tbl_init_buffer */
static void reset_alloc_info(void)
{
    ordTblAllocInfo.currPtr = ordTblAllocInfo.initPtr;
    ordTblAllocInfo.currSize = ordTblAllocInfo.initSize;
}

/* Sets the initial buffer and size to be used by 'ord_tbl_alloc_node' */
void ord_tbl_init_buffer(void *addr, u32 size)
{
    ordTblAllocInfo.initPtr = addr;
    ordTblAllocInfo.initSize = size;
    reset_alloc_info();
}

/* Inserts the node into the list after 'tblEntry' */
void ord_tbl_insert_node(struct OrdTblNode *tblEntry, struct OrdTblNode *newNode)
{
    newNode->next = tblEntry->next;
    tblEntry->next = newNode;
}

/* Allocates a block of memory from the buffer */
void *ord_tbl_alloc_node(u32 size)
{
    void *ptr;

    if (ordTblAllocInfo.currSize < size)
        OSPanic("ord_tbl.c", 328, "Ordering Primitive Over!!");
    ptr = ordTblAllocInfo.currPtr;
    ordTblAllocInfo.currPtr += size;
    ordTblAllocInfo.currSize -= size;
    return ptr;
}
