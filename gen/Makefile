PARSE_NAME=scriptEvalParse
EXPR_PARSE_NAME=scriptExprParse
OUTDIR=tmp

.PHONY: all
all: $(OUTDIR)/$(PARSE_NAME).c $(OUTDIR)/$(EXPR_PARSE_NAME).c
 
$(OUTDIR)/$(PARSE_NAME).c : eval.rl
	mkdir -p $(OUTDIR)
	ragel -C $< -o $@
	gcc -g $@ -DSCRIPT_EVAL_PARSE_TEST -o $(OUTDIR)/evalParseTest

$(OUTDIR)/$(EXPR_PARSE_NAME).c : expr.rl
	mkdir -p $(OUTDIR)
	ragel -C $< -o $@
	gcc -g $@ -DSCRIPT_EXPR_PARSE_TEST -o $(OUTDIR)/exprParseTest 
