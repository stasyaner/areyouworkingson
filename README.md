#hacktoberfest2022

### Details
The idea was to write a simple timetracker.
Due to time limitation, this idea boiled down to funny program, which connects
to google calendar and asks if you are working (son), when you have no ongoing
meetings.
A lot of challenges were faced, such as:
- how the heck can I connect to the google API?
- how the heck can I create a project?
- why the heck cannot I create a project outside of my organization?
- omg, screw that, just create me a project
- how the heck can I get an access token?
- omg, how hard it is to get an access token
- there is no openssl headers in macos

I installed openssl with homebrew, but
I ultimately failed at the point, when clang said that there is no openssl
headers for arm64. GG WP. :sadfrog:

Time was almost up and my journey stopped at compiling openssl for arm64.

#### Update as of 17 Oct 2022

Problem was due to I forgot to actually include the libs instead of just
providing a path to look for them.

### Links
https://dev.to/megazear7/google-calendar-api-integration-made-easy-2a68
https://gist.github.com/LindaLawton/cff75182aac5fa42930a09f58b63a309?permalink_comment_id=4232119#gistcomment-4232119
https://developers.google.com/identity/protocols/oauth2/service-account#httprest_1
https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
https://blog.andrewmadsen.com/2020/06/22/building-openssl-for.html
