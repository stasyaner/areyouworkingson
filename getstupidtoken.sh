#!/bin/bash
# Source: https://gist.github.com/LindaLawton/cff75182aac5fa42930a09f58b63a309?permalink_comment_id=4232119#gistcomment-4232119
###################################################
# Generate rs256 jwt just with cli commands and shell
# Specifically for gdrive service accounts usage
# Globals: None
# Arguments: 2
#   ${1} = service account json file contents ( should contain client_email and private key )
#   ${2} = SCOPE for gdrive ( if not given then global var SCOPE is used )
# Result: print jwt
# Refrences:
#   https://stackoverflow.com/questions/46657001/how-do-you-create-an-rs256-jwt-assertion-with-bash-shell-scripting
#   Inspired by implementation by Will Haley at:
#     http://willhaley.com/blog/generate-jwt-with-bash/
###################################################
_generate_jwt() {
    declare scope="https://www.googleapis.com/auth/calendar.readonly" aud="https://oauth2.googleapis.com/token" \
        header='{"alg":"RS256","typ":"JWT"}' \
        algo="256" scope payload_data iss exp iat rsa_secret signed_content sign

    if iss="XXXXX" &&
        rsa_secret="XXXXX"; then
        rsa_secret="$(printf "%b\n" "${rsa_secret}")"
    else
        printf "Error: Invalid service account file.\n" && return 1
    fi

    iat="1665746734" exp="$((iat + 3400))"

    b64enc() { : "$(openssl enc -base64 -A)" && : "${_//+/-}" && : "${_//\//_}" && printf "%s\n" "${_//=/}"; }

    payload_data='{"iss":"'${iss}'","scope":"'${scope}'","aud":"'${aud}'","exp":'${exp}',"iat":'${iat}'}'

    {
        signed_content="$(b64enc <<< "${header}").$(b64enc <<< "${payload_data}")"
        sign="$(printf %s "${signed_content}" | openssl dgst -binary -sha"${algo}" -sign <(printf '%s\n' "${rsa_secret}") | b64enc)"
    } || return 1

    printf '%s.%s\n' "${signed_content}" "${sign}"
    return 0
}

_generate_jwt
