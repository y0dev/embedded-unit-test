#include "mailbox.h"
#include "unit_test.h"
#include "mock_mailbox.h"
#include <string.h>

void test_mock_mailbox_send_receive_struct() {
    mock_mailbox_init();

    SensorData tx = { .id = 42, .value = 3.14f };
    strncpy(tx.label, "temperature", sizeof(tx.label));

    SensorData rx;

    AssertIntEQ(mock_mailbox_send(&tx, sizeof(tx)), 0);
    AssertIntEQ(mock_mailbox_receive(&rx, sizeof(rx)), 0);

    AssertIntEQ(rx.id, tx.id);
    AssertFloatEQ(rx.value, tx.value);
    AssertStrEQ(rx.label, tx.label);
}