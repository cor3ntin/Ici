import ici

def ici_print(ctx):
	for x in ctx.args():
		print(x)


conf = ici.ICISettings("../demo.ici")
conf.createFunction("print", ici_print);


if not conf.evaluate():
	print("error");

print conf.values()
