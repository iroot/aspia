//
// PROJECT:         Aspia
// FILE:            console/open_address_book_dialog.h
// LICENSE:         GNU Lesser General Public License 2.1
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_CONSOLE__OPEN_ADDRESS_BOOK_DIALOG_H
#define _ASPIA_CONSOLE__OPEN_ADDRESS_BOOK_DIALOG_H

#include "proto/address_book.pb.h"
#include "ui_open_address_book_dialog.h"

namespace aspia {

class OpenAddressBookDialog : public QDialog
{
    Q_OBJECT

public:
    OpenAddressBookDialog(QWidget* parent, proto::AddressBook::EncryptionType encryption_type);
    ~OpenAddressBookDialog();

    QString password() const;

private slots:
    void showPasswordButtonToggled(bool checked);
    void buttonBoxClicked(QAbstractButton* button);

private:
    Ui::OpenAddressBookDialog ui;

    Q_DISABLE_COPY(OpenAddressBookDialog)
};

} // namespace aspia

#endif // _ASPIA_CONSOLE__OPEN_ADDRESS_BOOK_DIALOG_H
