#ifndef DEBUGGER_H
#define DEBUGGER_H

void trace_enter();
void trace_leave();
void context_dump();
void checkpoint();


#ifdef DEBUG

#define TRACE_E(x)      void trace_enter(x);
#define TRACE_L(x)      void trace_leave(x);
#define PRINTF(x)       void debug_printf(x);
#define CTX_DMP(x)      void context_dump(x);
#define CHECKPOINT(x)   void checkpoint(x);

#else

#define TRACE_E(x)
#define TRACE_L(x)
#define PRINTF(x)
#define CTX_DMP(x)
#define CHECKPOINT(x)

#endif /* DEBUG */


#endif /* DEBUGER_H */