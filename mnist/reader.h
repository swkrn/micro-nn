#ifndef READER_H
#define READER_H

#include <stdint.h>
#include <stdio.h>

struct Images {
    uint8_t **images;
    uint8_t *labels;
    uint32_t n;
    uint32_t each_width;
    uint32_t each_height;
    uint32_t each_size;
};

int reader_read_images(
    const char *images_filename,
    const char *labels_filename,
    struct Images *images
);
void reader_show_images(struct Images *images, int begin_index, int n);

#endif
