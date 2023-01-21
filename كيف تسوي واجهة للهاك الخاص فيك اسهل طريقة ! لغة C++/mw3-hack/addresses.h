#pragma once

namespace addresses
{
	typedef void(*Cbuf_AddText_t)(int clientNum, const char* command);
	extern Cbuf_AddText_t Cbuf_AddText;
}