#ifndef FUACTIVEKEY_H
#define FUACTIVEKEY_H

#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QDateTime>

class FUActiveKey {
public:
    // 암호화 및 복호화에 사용할 키 (예: 16바이트 키)
    FUActiveKey() {
        m_key = "mysecretkey12345";
    }

    //// 4자리 숫자를 암호화
    //QString encrypt(const QString &number) {
    //    if (number.length() != 4 || !number.toInt()) {
    //        qDebug() << "Invalid 4-digit number";
    //        return QString();
    //    }
    //
    //    QByteArray data = number.toUtf8();
    //    QByteArray encrypted;
    //
    //    // 간단한 XOR 암호화
    //    for (int i = 0; i < data.size(); ++i) {
    //        encrypted.append(data[i] ^ m_key[i % m_key.size()]);
    //    }
    //
    //    // Base64로 인코딩하여 저장
    //    return QString(encrypted.toBase64());
    //}

    // 암호화된 데이터를 복호화
    QString decrypt(const QString &encrypted) {
        QByteArray encryptedData = QByteArray::fromBase64(encrypted.toUtf8());
        QByteArray decrypted;

        // 동일한 XOR 연산으로 복호화
        for (int i = 0; i < encryptedData.size(); ++i) {
            decrypted.append(encryptedData[i] ^ m_key[i % m_key.size()]);
        }

        QString result = QString(decrypted);
        if (result.length() != 4 || !result.toInt()) {
            qDebug() << "Decryption failed or invalid number";
            return QString();
        }

        return result;
    }

    QStringList pressure = {"X09AUQ==",
                             "WEpHUQ==",
                             "W05LXA==",
                             "XUBBVw==",
                             "VUBDVA==",
                             "WUxFUg==",
                             "WkFKVQ==",
                             "Xk1GUw==",
                             "VElCVw==",
                             "VElCVw==",
                             "X0hAUQ==",
                             "VU5FUA==",
                             "WUpBVA==",
                             "XUBLUg==",
                             "W0xHVg==",
                             "XktCVQ==",
                             "VEFEUw==",
                             "WE1AVw==",
                             "XElKXQ==",
                             "XElKXQ==",
                             "X0pHVA==",
                             "W05LVQ==",
                             "XEtAXA==",
                             "VUBDUg==",
                             "WUxFVg==",
                             "WkFKVw==",
                             "Xk1GVA==",
                             "VElCXQ==",
                             "WE9EVQ==",
                             "WE9EVQ==",
                             "VU5FXA==",
                             "WUpBUg==",
                             "XUBLVg==",
                             "W0xHVA==",
                             "XktCXA==",
                             "VEFEUQ==",
                             "WE1AVQ==",
                             "XElKUw==",
                             "Wk9GVw==",
                             "Wk9GVw==",
                             "W05LUA==",
                             "XEtAVw==",
                             "VUBDXA==",
                             "WUxFVA==",
                             "WkFKXQ==",
                             "Xk1GXA==",
                             "VElCUQ==",
                             "WE9EUw==",
                             "X0hAVQ==",
                             "X0hAVQ==",
                             "WUpBVg==",
                             "XUBLUA==",
                             "W0xHUg==",
                             "XktCUA==",
                             "VEFEVQ==",
                             "WE1AXQ==",
                             "XElKVw==",
                             "Wk9GVQ==",
                             "X0pHVg==",
                             "X0pHVg==",
                             "XEtAUw==",
                             "VUBDUA==",
                             "WUxFXA==",
                             "WkFKUQ==",
                             "Xk1GUg==",
                             "VElCVQ==",
                             "WE9EVw==",
                             "X0hAUw==",
                             "VU5FUg==",
                             "VU5FUg==",
                             "XUBLVA==",
                             "W0xHXA==",
                             "XktCUg==",
                             "VEFEVw==",
                             "WE1AUQ==",
                             "XElKVQ==",
                             "Wk9GXQ==",
                             "X0pHXA==",
                             "W05LVg==",
                             "W05LVg==",
                             "VUBDVg==",
                             "WUxFUA==",
                             "WkFKUw==",
                             "Xk1GVg==",
                             "VElCUw==",
                             "WE9EUQ==",
                             "X0hAVw==",
                             "VU5FVg==",
                             "WUpBXA==",
                             "WUpBXA==",
                             "W0xHUA==",
                             "XktCVg==",
                             "VEFEXQ==",
                             "WE1AUw==",
                             "XElKUQ==",
                             "Wk9GUw==",
                             "X0pHVQ==",
                             "W05LUg==",
                             "XEhGVg==",
                             "XUxHVA=="};

    QString GetKey()
    {
        int idx = QDateTime::currentDateTime().date().year() - 2025;

        return decrypt(pressure[idx]);
    }

private:
    QByteArray m_key;
};
#endif // FUACTIVEKEY_H
