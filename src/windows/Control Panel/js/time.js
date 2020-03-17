window.onload=function()
{
    setInterval("UpdateTime()",100);
}
function UpdateTime()
{
    var current_time=new Date();
    var year=current_time.getFullYear();
    var month=current_time.getMonth();
    var day=current_time.getDate();
    var hour=current_time.getHours();
    var minute=current_time.getMinutes();
    var second=current_time.getSeconds();
    if(hour<10)
        hour="0"+hour;
    if(minute<10)
        minute="0"+minute;
    if(second<10)
        second="0"+second;
    var nowtime=year+"/"+month+"/"+day+" "+hour+":"+minute+":"+second;
    document.getElementById("time").innerHTML=nowtime;
}