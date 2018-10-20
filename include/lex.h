#pragma once
#include<token.h>
#include<tstring.h>
#include<ttypes.h>

Token get_token(string code);
DARRAY(token) get_tokens(string code);
