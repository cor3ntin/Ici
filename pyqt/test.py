import ici

def ici_print(ctx):
    print("hello")
    for x in ctx.args():
            print(x)

def uber_fun(ctx):
    return [42, {}, ["lol"]]

conf = ici.ICISettings("demo.ici")
print(conf.createFunction("print", ici_print))
print(conf.createFunction("uber", uber_fun))

if not conf.evaluate():
    print(conf.errorString());
