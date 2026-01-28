<cfcontent type="text/plain">

<cfloop collection="#CGI#" item="key">
    #key# = #CGI[key]#
</cfloop>