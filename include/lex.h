#pragma once
#include<token.h>
#include<tstring.h>
#include<ttypes.h>

Token get_token(String code);
DARRAY(Token) get_tokens(String code);
