/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Format.h>
#include <AK/NumericLimits.h>

namespace GUI {

class TextPosition {
public:
    TextPosition() = default;
    TextPosition(size_t line, size_t column)
        : m_line(line)
        , m_column(column)
    {
    }

    bool is_valid() const { return m_line != AK::NumericLimits<size_t>::max() && m_column != AK::NumericLimits<size_t>::max(); }

    size_t line() const { return m_line; }
    size_t column() const { return m_column; }

    void set_line(size_t line) { m_line = line; }
    void set_column(size_t column) { m_column = column; }

    bool operator==(TextPosition const& other) const { return m_line == other.m_line && m_column == other.m_column; }
    bool operator!=(TextPosition const& other) const { return m_line != other.m_line || m_column != other.m_column; }
    bool operator<(TextPosition const& other) const { return m_line < other.m_line || (m_line == other.m_line && m_column < other.m_column); }
    bool operator>(TextPosition const& other) const { return *this != other && !(*this < other); }
    bool operator>=(TextPosition const& other) const { return *this > other || (*this == other); }

private:
    size_t m_line { AK::NumericLimits<size_t>::max() };
    size_t m_column { AK::NumericLimits<size_t>::max() };
};

}

template<>
struct AK::Formatter<GUI::TextPosition> : AK::Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, GUI::TextPosition const& value)
    {
        if (value.is_valid())
            return Formatter<FormatString>::format(builder, "({},{})"sv, value.line(), value.column());

        return builder.put_string("GUI::TextPosition(Invalid)"sv);
    }
};
