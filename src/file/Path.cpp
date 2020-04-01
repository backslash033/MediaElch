#include "file/Path.h"

namespace mediaelch {

QString DirectoryPath::toNativePathString() const
{
    return QDir::toNativeSeparators(toString());
}

bool DirectoryPath::isParentFolderOf(const DirectoryPath& child)
{
    return toString().startsWith(child.toString());
}

QString DirectoryPath::filePath(const QString& fileName) const
{
    return m_dir.filePath(fileName);
}

DirectoryPath DirectoryPath::subDir(const QString& dirName) const
{
    return {toString() + '/' + dirName};
}


bool operator==(const DirectoryPath& lhs, const DirectoryPath& rhs)
{
    return lhs.toString() == rhs.toString();
}

bool operator!=(const DirectoryPath& lhs, const DirectoryPath& rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const DirectoryPath& dir)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "DirectoryPath(" << dir.toString() << ')';
    return debug;
}


bool operator==(const FilePath& lhs, const FilePath& rhs)
{
    return lhs.toString() == rhs.toString();
}

bool operator!=(const FilePath& lhs, const FilePath& rhs)
{
    return !(lhs == rhs);
}

QDebug operator<<(QDebug debug, const FilePath& dir)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "FilePath(" << dir.toString() << ')';
    return debug;
}

QString FilePath::toNativePathString() const
{
    return QDir::toNativeSeparators(toString());
}

DirectoryPath FilePath::dir() const
{
    return DirectoryPath(m_fileInfo.dir());
}


} // namespace mediaelch