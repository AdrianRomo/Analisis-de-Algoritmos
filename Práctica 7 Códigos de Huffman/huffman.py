def assign_code(nodes, label, result, prefix = ''):
	childs = nodes[label]
	tree = {}
	if len(childs) == 2:
		tree['0'] = assign_code(nodes, childs[0], result, prefix + '0')
		tree['1'] = assign_code(nodes, childs[1], result, prefix + '1')
		return tree
	else:
		result[label] = prefix
		return label

def Huffman_code(_vals):
	vals = _vals.copy()
	nodes = {}
	for n in vals.keys(): # leafs initialization
		nodes[n] = []

	while len(vals) > 1: # binary tree creation
		s_vals = sorted(vals.items(), key=lambda x:x[1])
		a1 = s_vals[0][0]
		a2 = s_vals[1][0]
		vals[a1 + a2] = vals.pop(a1) + vals.pop(a2)
		nodes[a1 + a2] = [a1, a2]
	code = {}
	root = a1 + a2
	tree = {}
	tree = assign_code(nodes, root, code)   # assignment of the code for the given binary tree
	return code, tree

freq = [
(6.8, 'a'), (1.3, 'b'), (2.6, 'c'), (3.5, 'd'),
(10.2, 'e'),(1.8, 'f') ]
vals = {l:v for (v,l) in freq}
code, tree = Huffman_code(vals)

text = 'c' # text to encode
encoded = ''.join([code[t] for t in text])
print('Encoded text:',encoded)
decoded = []
i = 0
while i < len(encoded): # decoding using the binary grap
	ch = encoded[i]
	act = tree[ch]
	while not isinstance(act, str):
		i += 1
		ch = encoded[i]
		act = act[ch]
	decoded.append(act)
	i += 1
print('Decoded text:','\n'.join(decoded))

def draw_tree(tree, prefix = ''):
	if isinstance(tree, str):
		descr = 'N%s [label="%s:%s", fontcolor=blue, fontsize=16, width=2, shape=box];\n'%(prefix, tree, prefix)
	else: # Node description
		descr = 'N%s [label="%s"];\n'%(prefix, prefix)
		for child in tree.keys():
			descr += draw_tree(tree[child], prefix = prefix+child)
			descr += 'N%s -> N%s;\n'%(prefix,prefix+child)
	return descr

import subprocess
with open('graph.dot','w') as f:
	f.write('digraph G {\n')
	f.write(draw_tree(tree))
	f.write('}')
subprocess.call('dot -Tpng graph.dot -o graph.png', shell=True)
