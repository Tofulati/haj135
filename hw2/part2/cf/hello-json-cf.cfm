<cfcontent type="application/json">

<cfset response = {
    team = "HAJ135",
    message = "Hello JSON ColdFusion - Albert, Hajin, Joey",
    language = "ColdFusion",
    generated_at = DateTimeFormat(Now(), "mm-dd-YYYY HH:nn:ss"),
    ip = CGI.REMOTE_ADDR
}>

#SerializeJSON(reponse)#