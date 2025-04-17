#include "mock_mailbox.h"
#include <string.h>
#include <stdio.h>

#define MAILBOX_BUFFER_SIZE 256

static unsigned char mailbox_storage[MAILBOX_BUFFER_SIZE];
static size_t mailbox_data_size = 0;

void mock_mailbox_init(void) {
    mailbox_data_size = 0;
    memset(mailbox_storage, 0, sizeof(mailbox_storage));
}

int mock_mailbox_send(const void* data, size_t size) {
    if (size > MAILBOX_BUFFER_SIZE) {
        return -1;  // too big
    }
    memcpy(mailbox_storage, data, size);
    mailbox_data_size = size;
    return 0;
}

int mock_mailbox_receive(void* buffer, size_t size) {
    if (mailbox_data_size == 0 || size < mailbox_data_size) {
        return -1;  // nothing to receive or buffer too small
    }
    memcpy(buffer, mailbox_storage, mailbox_data_size);
    return 0;
}
