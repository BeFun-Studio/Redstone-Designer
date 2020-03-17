if(!window.applicationCache)
{
    if(showBrowserDoesNotSupportHTML5Warning)
        alert("Your browser does not support HTML 5, some functions will be disabled.");
    document.write("<p id=\"top_prompt_bar\"><img src=\"img/warning.ico\" height=\"16\" width=\"16\" />Your browser does not support HTML 5, please upgrade your browser.</p>")
}
else
    browserDoesNotSupportHTML5=false;