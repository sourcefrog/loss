env = Environment(CFLAGS='-Wall -g -Werror', CC='clang')

common_src = [
    'alist.c',
    'builtin.c',
    'parse.c', 'int.c', 'list.c', 'print.c',
    'str.c',
    'sym.c']

env.Program('loss',
    ['loss.c', 'eval.c'] + common_src)

# Parse and print, but don't evaluate
env.Program('loss_parse',
    ['loss_parse.c', 'parse.c', 'str.c', 'int.c', 'print.c', 'list.c', 'sym.c'])

# Run some parser tests
env.Command('check',
    ['loss', 'loss_parse'],
    './test.sh')

# vim: et sw=4 ft=python
