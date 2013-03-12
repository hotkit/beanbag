import httplib2
from simplejson import dumps

m, gtf = httplib2.Http().request('http://jtv.home.xs4all.nl/gtf/GPL_TLA_FAQ')
assert m['status'] == '200', m

database = {'meta': m}


for line in gtf.split('\n'):
    if line:
        tla, definition = line.split('\t')
        if database.has_key(tla):
            database[tla].append(definition)
        else:
            database[tla] = [definition]

file('database.json', 'w').write(dumps(database))
