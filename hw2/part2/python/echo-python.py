<cfsetting enablecfoutputonly="yes">
<cfcontent type="application/json" reset="true">

<cfscript>
    method = CGI.REQUEST_METHOD;

    data = structNew();

    if (method eq "GET") {
        for (key in URL) {
            data[key] = URL[key];
        }
    } else {
        for (key in FORM) {
            data[key] = FORM[key];
        }

        rawBody = ToString(GetHttpRequestData().content);
        if (len(trim(rawBody))) {
            try {
                parsed = deserializeJSON(rawBody);
                for (k in parsed) {
                    data[k] = parsed[k];
                }
            } catch (any e) {

            }
        }
    }

    data["_method"] = method;
    data["_timestamp"] = dateFormat(now(), "mm-dd-yyyy");
    data["_ip"] = CGI.REMOTE_ADDR;
    data["_host"] = CGI.SERVER_NAME;
    data["_user_agent"] = CGI.HTTP_USER_AGENT;

    writeOutput(serializeJSON(data));
</cfscript>