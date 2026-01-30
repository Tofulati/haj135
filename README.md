# HAJ135 - CSE135

## Team Members
- Albert Ho
- Joseph Kim
- Hajin Park

## Grader Account Access Info
- **Username:** grader
- **Password:** grader135

## Apache Server Access
- ```{user}@64.23.226.243```
- Each auth user has a password
- Root access only for system admin
- To access mysql the command below using the root user password when prompted:
```> mysql -u root -p```

## Live Website
- **URL:** https://haj135.site/
- **Includes:**
  - Homepage with member info and homework links
  - Individual pages about team members
  - Favicon
  - robots.txt
  - Homework pages and files
- **Login Information:**
  - User: same as ssh (i.e. grader)
  - Password: same as ssh (i.e. grader135)

## GitHub Auto-Deploy Setup
- **Overview:**
  - Code is pushed from local machine to bare Git repo on server
  - A ```post-recieve``` hook checks out latest version on main branch
  - Files are copied over ("deployed") to Apache web root directory
  - Latest version on local main branch is pushed to remote Github repository (for visibility/collaboration)
  - Root access isn't required for deployment (`prod` alias may point to any existing user on the server)
- **Deployment Flow:**
  1. Developer commits changes locally
  2. Developer pushes to production remote 
  3. Git hook executes on server
  4. Website/Github updates automatically
- **Server Paths:**
  - Bare Git repo: ```/var/repo/haj135.git```
  - Web root: ```/var/www/haj135.site```
  - Github repository: ```https://github.com/Tofulati/haj135.git```
  - Deployment hook: ```/var/repo/haj135.git/hooks/post-receive```
  - Deployment log: ```/var/log/deploy-haj135.log```

## Deployment Command
Run the following once:
```git remote add prod ssh://<username>@64.23.226.243/var/repo/haj135.git```

if prod already exists:
```git remote set-url prod ssh://<username>@64.23.226.243/var/repo/haj135.git```

After setup, use this command to push to prod:
```git push prod```

## Deployment Demo
A demo GIF showing the full deployment pipeline
![GitHub Auto Deploy Demo](GitHub-Deploy.gif)

## Compression Answers
When we enabled mod_deflate on the server, we noticed that the size of the network transferred was much smaller than that of the resource sizes. This was probably a result of the compression of the files when being transferred from the server. Moreover, we noticed that the request headers included deflate and gzip within its ```Accept-Encoding``` header. 

## Obscure Server Identity
In order to do this, we installed ```sudo apt install libapache2-mod-security2``` in apache2.conf. Within this file, we had to make sure that the serversignature was off, in order for us to change the header. In addition to this, we updated servertokens to production, such that when we push to the live server, it would change the tokens. Finally, we updated the secserversignature to force the server header to be what we wanted, in this case "CSE 135 Server." These changes were made through altering the security of the apache server and forcing the headers to be what we wanted.
