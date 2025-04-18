#ifndef MAILBOX_H__
#define MAILBOX_H__

typedef struct {
    int id;
    float value;
    char label[16];
} SensorData;

void test_mock_mailbox_send_receive_struct(void);

#endif