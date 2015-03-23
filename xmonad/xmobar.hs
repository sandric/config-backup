-- xmobar config used by Vic Fryzel
-- Author: Vic Fryzel
-- http://github.com/vicfryzel/xmonad-config

-- This is setup for dual 1920x1080 monitors, with the right monitor as primary
Config {
    font = "-misc-fixed-*-*-*-*-10-*-*-*-*-*-*-*",
    borderColor = "black",
    border = TopB,
    bgColor = "black",
    fgColor = "grey",
    position = Top,
    lowerOnStart = True,
    pickBroadest = False,
    persistent = False,
    hideOnStart = False,
    allDesktops = True,
    overrideRedirect = True,

    commands = [
        Run Cpu ["-L","3","-H","50","--normal","green","--high","red"] 10,
        Run Memory ["-t","Mem: <usedratio>%","-H","8192","-L","4096","-h","#FFB6B0","-l","#CEFFAC","-n","#FFFFCC"] 10,
        Run Swap ["-t","Swap: <usedratio>%","-H","1024","-L","512","-h","#FFB6B0","-l","#CEFFAC","-n","#FFFFCC"] 10,
        Run Network "wlan0" ["-L","0","-H","32","--normal","green","--high","red"] 10,
        Run Network "eth0" ["-L","0","-H","32","--normal","green","--high","red"] 10,
        Run Date "%a %b %_d %k:%M" "date" 10,
        Run StdinReader
    ],
    sepChar = "%",
    alignSep = "}{",
    template = "%StdinReader% %cpu% %memory% %swap% | %wlan0% %eth0% }{ <fc=#ee9a00>%date%</fc>"
}
