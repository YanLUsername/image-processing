/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *newList = (ILIST *)malloc(sizeof(ILIST));
        assert(newList);

        newList->Length = 0;
        newList->First = NULL;
        newList->Last = NULL;

        return newList;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	IENTRY *current = list->First;
        while (current) {
                IENTRY *next = current->Next;
                DeleteYUVImage((YUVImage *)current->image);
                free(current);
                current = next;
        }
        free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
	assert(list);
	assert(RGBimage);

        IENTRY *newEntry = (IENTRY *)malloc(sizeof(IENTRY));
	assert(newEntry);

        newEntry->image = (void *)RGBimage;
        newEntry->Next = NULL;
        newEntry->Prev = list->Last;
        newEntry->List = list;

        if (list->Last) {
                list->Last->Next = newEntry;
        } 
	else {
                list->First = newEntry;
        }

        list->Last = newEntry;
        list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{
	assert(list);
	assert(YUVimage);

        IENTRY *entry = (IENTRY *)malloc(sizeof(IENTRY));
	assert(entry);

        entry->image = (void *)YUVimage;
        entry->Next = NULL;
        entry->Prev = list->Last;
        entry->List = list;

        if (list->Last) {
                list->Last->Next = entry;
        } 
	else {
                list->First = entry;
        }

        list->Last = entry;
        list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);
	assert(list->Length > 0);

        IENTRY *entry = list->First;
        int index = 0;

        while (entry) {
                IENTRY *next = entry->Next;
		if (index < start || index > end) {
                        if (entry->Prev) {entry->Prev->Next = entry->Next;}
                        if (entry->Next) {entry->Next->Prev = entry->Prev;}
                        if (entry == list->First) {list->First = entry->Next;}
                        if (entry == list->Last) {list->Last = entry->Prev;}
                        DeleteImage(entry->image);
                        free(entry);
                        list->Length--;
                }
                entry = next;
		index = index + 1;
        }
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	assert(factor >= 1);
	assert(list->Length > 0);

        IENTRY *entry = list->First;
        int index = 0;

        while (entry) {
                IENTRY *next = entry->Next;
                if (index % factor != 0) {
                        if (entry->Prev) {entry->Prev->Next = entry->Next;}
                        if (entry->Next) {entry->Next->Prev = entry->Prev;}
                        if (entry == list->First) {list->First = entry->Next;}
                        if (entry == list->Last) {list->Last = entry->Prev;}
                        DeleteImage(entry->image);
                        free(entry);
                        list->Length--;
                }
                entry = next;
		index = index + 1;
        }
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list->Length > 1);

        IENTRY *current = list->First;
        IENTRY *temp = NULL;
        while (current) {
                temp = current->Next;
                current->Next = current->Prev;
                current->Prev = temp;
                current = temp;
        }
        temp = list->First;
        list->First = list->Last;
        list->Last = temp;
}

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
	assert(list);
	assert(RGBimage);

        IENTRY *entry = (IENTRY *)malloc(sizeof(IENTRY));
        assert(entry);

        entry->image = (void *)RGBimage;
        entry->Next = list->First;
        entry->Prev = NULL;
        entry->List = list;

        if (list->First) {
                list->First->Prev = entry;
        } else {
                list->Last = entry;
        }

        list->First = entry;
        list->Length++;
}
/* EOF */
