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
  - Files are deployed to Apache web root
  - Root access isn't required for deployment (as long as user on server)
- **Deployment Flow:**
  1. Developer commits changes locally
  2. Developer pushes to production remote 
  3. Git hook executes on server
  4. Website updates automatically
- **Server Paths:**
  - Bare Git repo: ```/var/repo/haj135.git```
  - Web root: ```/var/www/haj135.site/public_html```
  - Deployment hook: ```/var/repo/haj135.git/hooks/post-receive```
  - Deployment log: ```/var/log/deploy-haj135.log```

## Deployment Command
Run the following once:
```git remote set-url prod ssh://<username>@64.23.226.243/var/repo/haj135.git```

After setup, use this command to push to prod:
```git push prod main```

## Deployment Demo
A demo GIF showing the full deployment pipeline
![GitHub Auto Deploy Demo](GitHub-Deploy.gif)

## Compression Answers
When we enabled mod_deflate on the server, we noticed that the size of the network transferred was much smaller than that of the resource sizes. This was probably a result of the compression of the files when being transferred from the server. Moreover, we noticed that the request headers included deflate and gzip within its ```Accept-Encoding``` header. 

