from turtle import dot
from graphviz import Source

ast = Source.from_file('output.dot', format='png', engine='dot')

ast.view(filename='output', cleanup=True, quiet_view=True)
