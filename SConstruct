env = Environment(CFLAGS='-Wall -g', CC='clang')

common_src = [
    'parse.c', 'int.c', 'list.c', 'print.c',
    'str.c',
    'sym.c']

env.Program('loss',
    ['loss.c'] + common_src)

# Parse and print, but don't evaluate
env.Program('loss_parse',
    ['loss_parse.c'] + common_src)

# Run some parser tests
env.Command('check',
    ['loss', 'loss_parse'],
    './test.sh')

# vim: et sw=4 ft=python
