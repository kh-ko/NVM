pragma Singleton
import QtQuick 2.0

Item {
    function log10(value)
    {
        if(value === 0 || value < 0)
        {
            value = 0.00000000000001
        }
        return Math.log(value) /  Math.log(10)
    }

    function log10round(value)
    {
        return Math.round(log10(value))
    }

    function floor(value)
    {
        var sign  = value < 0 ? -1 : 1
        var abs   = Math.abs(value)
        abs = abs + (abs * 0.000000001)
        value = Math.floor(abs) * sign
        return value
    }
}
