#include "file/NameFormatter.h"

#include <QRegularExpression>
#include <QStringList>

NameFormatter::NameFormatter(QStringList excludeWords, QObject* parent) : QObject(parent), m_excludedWords{excludeWords}
{
    std::sort(m_excludedWords.begin(), m_excludedWords.end(), NameFormatter::lengthLessThan);
}

QString NameFormatter::excludeWords(QString name)
{
    const QStringList braces = {".", "(", ")", "[", "]", "<", ">"};
    QRegularExpression rx;
    rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match;

    for (const QString& word : m_excludedWords) {
        if (braces.contains(word)) {
            // Check if the word is a brace...
            name.replace(word, "");
            continue;
        }
        // ...or ignore words with special characters... (TODO: may not be safe)
        rx.setPattern("[$&+,:;=?@#|'<>.^*()%!-]");
        if (rx.match(word).hasMatch()) {
            continue;
        }
        // ...otherwise who knows how this regex would look like
        rx.setPattern(R"((^|[-_(\s.[,]+))" + word + R"(([-_\s.)\],]+|$))");
        if (!rx.isValid()) {
            continue;
        }
        match = rx.match(name);
        int pos = match.capturedStart();
        while (pos >= 0) {
            name = name.remove(pos, match.captured(0).length());
            name = name.insert(pos, ' ');
            match = rx.match(name);
            pos = match.capturedStart();
        }
    }

    // remove "- _" at the end of a name
    rx.setPattern("[-\\s_]");
    while (name.length() > 0 && name.lastIndexOf(rx) == name.length() - 1) {
        name.chop(1);
    }
    // remove spaces at the start end end which may have been introduced
    return name.trimmed();
}

QString NameFormatter::formatName(QString name, bool replaceDots, bool replaceUnderscores)
{
    if (replaceDots) {
        name = name.replace(".", " ");
    }

    if (replaceUnderscores) {
        name = name.replace("_", " ");
    }

    // remove exclude words
    name = excludeWords(name);

    // remove resulting empty brackets
    QRegularExpression rx(R"(\([-\s]*\))");
    QRegularExpressionMatch match = rx.match(name);
    int pos = match.capturedStart();
    while (pos >= 0) {
        name = name.remove(pos, match.captured(0).length());
        match = rx.match(name);
        pos = match.capturedStart();
    }

    // remove " - _" at the end of a name
    rx.setPattern("[-\\s_]");
    while (name.length() > 0 && name.lastIndexOf(rx) == name.length() - 1) {
        name.chop(1);
    }
    return name;
}

QString NameFormatter::removeParts(QString name)
{
    QRegularExpression rx(R"re([-_\s().]+([a-f]|(?:(?:part|cd|xvid)[-_\s.]*\d+))[-_\s().]*$)re",
        QRegularExpression::CaseInsensitiveOption);
    int pos = name.lastIndexOf(rx);
    name = name.left(pos);
    return name;
}

bool NameFormatter::lengthLessThan(const QString& s1, const QString& s2)
{
    return s1.length() > s2.length();
}
