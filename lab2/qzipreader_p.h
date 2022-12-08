#ifndef QZIPREADER_P_H
#define QZIPREADER_P_H
//#include <QtGui/private/qtguiglobal_p.h>
#include <QtCore/qglobal.h>

#ifndef QT_NO_TEXTODFWRITER

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QZipReader class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qdatetime.h>
#include <QtCore/qfile.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QZipReaderPrivate;

class QZipReader
{
public:
    explicit QZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly );

    explicit QZipReader(QIODevice *device);
    ~QZipReader();

    QIODevice* device() const;

    bool isReadable() const;
    bool exists() const;

    struct FileInfo
    {
        FileInfo() noexcept  : isDir(false), isFile(false), isSymLink(false), crc(0), size(0)  {}

        bool isValid() const noexcept { return isDir || isFile || isSymLink; }
        QString filePath;
        uint isDir : 1;
        uint isFile : 1;
        uint isSymLink : 1;
        QFile::Permissions permissions;
        uint crc;
        qint64 size;
        QDateTime lastModified;
    };

    QVector<FileInfo> fileInfoList() const;
    int count() const;

    FileInfo entryInfoAt(int index) const;
    QByteArray fileData(const QString &fileName) const;
    bool extractAll(const QString &destinationDir) const;

    enum Status {
        NoError,
        FileReadError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    Status status() const;

    void close();

private:
    QZipReaderPrivate *d;
    Q_DISABLE_COPY_MOVE(QZipReader) ;};
Q_DECLARE_TYPEINFO(QZipReader::FileInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(QZipReader::Status, Q_PRIMITIVE_TYPE);

QT_END_NAMESPACE
#endif // QZIPREADER_P_H
#endif
