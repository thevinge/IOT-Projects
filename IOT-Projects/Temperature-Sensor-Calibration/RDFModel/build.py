from rdflib import Literal

from wrapper import *

def query(g, q):
    r = g.query(q)
    return list(map(lambda row: list(row), r))


g = model()

functionMin = IOT['/function/min']
functionMax = IOT['/function/max']
functionAvg = IOT['/function/mean']


g.add((functionMin, RDF.type, IOT.Function))
g.add((functionMin, IOT.isType, IOT.LinearFunction))
g.add((functionMin, IOT.a, Literal(0.0678319, datatype=XSD.float)))
g.add((functionMin, IOT.b, Literal(-26.1284, datatype=XSD.float)))
g.add((functionMin, IOT.name, Literal("Min",datatype=XSD.string)))

g.add((functionMax, RDF.type, IOT.Function))
g.add((functionMax, IOT.isType, IOT.LinearFunction))
g.add((functionMax, IOT.name, Literal("Max",datatype=XSD.string)))
g.add((functionMax, IOT.a, Literal(0.0658076, datatype=XSD.float)))
g.add((functionMax, IOT.b, Literal(-26.0289, datatype=XSD.float)))

g.add((functionAvg, RDF.type, IOT.Function))
g.add((functionAvg, IOT.isType, IOT.LinearFunction))
g.add((functionAvg, IOT.name, Literal("Mean",datatype=XSD.string)))
g.add((functionAvg, IOT.a, Literal(0.0627918, datatype=XSD.float)))
g.add((functionAvg, IOT.b, Literal(-20.9698, datatype=XSD.float)))


g.serialize("rdfModel.ttl", 'turtle')


# thermistor to the 3 functions
q_function_info = '''
    SELECT DISTINCT  ?a ?b ?name ?function_type ?function
    WHERE {
        ?function       rdf:type                  iot:Function .
        ?function       iot:b                     ?b .
        ?function       iot:a                     ?a .
        ?function       iot:name                  ?name .
        ?function       iot:isType                ?function_type . 
    }
    '''

results = query(g, q_function_info)
print(results)