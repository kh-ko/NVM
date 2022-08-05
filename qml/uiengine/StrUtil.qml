pragma Singleton
import QtQuick 2.0
import FontManager 1.0

Item {
    function realNumberCalcFixedN(target, fixedN)
    {
        var searchIdx
        var fixedValue = 0;
        var dotIdx = target.indexOf(".")

        if(dotIdx !== -1)
        {
            for(searchIdx = 1; (searchIdx + dotIdx) < target.length && searchIdx <= fixedN; searchIdx++)
            {
                if(target.charAt(searchIdx + dotIdx) !== "0")
                    fixedValue = searchIdx
            }
        }

        return fixedValue
    }

    function realNumberToString(target, fixedN)
    {
        var strNumber = target.toFixed(fixedN)//toLocaleString(FontManager.locale,'f',fixedN)
        strNumber = strNumber.replace(',','');

        var searchIdx
        var fixedValue = 0;
        var dotIdx = strNumber.indexOf(".")

        if(dotIdx !== -1)
        {
            for(searchIdx = dotIdx + 1; searchIdx < strNumber.length; searchIdx++)
            {
                if(target.charAt(searchIdx + dotIdx) !== "0")
                    fixedValue = searchIdx
            }

            return strNumber.substr(0, fixedValue + 1)
        }

        return strNumber
    }

    function msecToString(msec)
    {
        if(msec < 0)
            msec = 0

        var temp = parseInt(msec / 1000);
        var hour = parseInt(temp / 3600);
        var min  = parseInt((temp % 3600)/60);
        var sec  = temp %  60                ;

        return hour.toString().padStart(2,'0') + ':' + min.toString().padStart(2, '0') + ':' + sec.toString().padStart(2, '0');
    }
}
