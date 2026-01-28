<cfset team = "HAJ135">
<cfset lang = "ColdFusion">
<cfset datetime = Now()>
<cfset ip = CGI.REMOTE_ADDR>

<!DOCTYPE html>
<html>
    <head>
        <title>Hello HTML ColdFusion</title>
    </head>
    <body>
        <h1>Hello from #team#</h1>
        <p>Welcome to the HTML ColdFusion page</p>
        <p>Generated at: #DateTimeFormat(datetime, "mm-dd-yyyy HH:nn:ss")#</p>
        <p>Your IP address: #ip#</p>
    </body>
</html>