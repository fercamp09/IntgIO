Querys para Neo4J

Match(john {name: 'John'})-[:friend]_>()-[:friend]->(fof)
return john.name, fof.name
+----------------------+
| john.name | fof.name |
+----------------------+
| "John"    | "Maria"  |
| "John"    | "Steve"  |
+----------------------+
2 rows


//Insercion de datos con relaciones.
Create (adam:User {name:'Adam'}),(pernilla:User {name:'Pernilla'}), (david:User{name:'David'}), (adam)-[:Friend]->(pernilla),(pernilla)-[:Friend]->(david);

//create- Device-Object-Action
create(device: Device{code:'000060',ip:'192.168.65.237',online:'true',model:'UNO',type:'Rasperry'}), (object:Object {code:'000061', name:'led',type:'sc'}), (action: Action{Status:'ON',code:'000062'}), (device)-[:HAVE]->(object),(object)-[:HAVE]->(action)

//select Device
match(device {code:{code}})-[:HAVE]->(object)-[:HAVE]->(action) return device,object,action

// seleccion Dispositivo y sus enlaces
MATCH (device{code:'000011'})-[:HAVE]->(object)-[:HAVE]->(action)
MATCH (object)<-[:link]->(objects)<-->(actions)
RETURN device, object, action, objects, actions

//eliminar relaciones, el id es el de la relacion 
start r=rel(id) delete r;

[{"id":"207af868.b1a418","type":"neo4j","z":"a1407d8a.ce131","name":"INFO NODE","url":"http://neo4j:integradora@127.0.0.1:7474","query":"MATCH (a:Action {code:{code} })\nRETURN a","x":442,"y":309.76422119140625,"wires":[["8324463.ab4d3b8","f2fc9981.8fd4b"]]}]

[{"id":"4e20926b.a5a7dc","type":"neo4j","z":"bc9bf4a0.4820e","name":"ONLY_OBJECTS2","url":"http://neo4j:integradora@127.0.0.1:7474","query":
"MATCH (device{code:{code}})-->(object)<-->(objects)
MATCH (objects)<-[:HAVE]->(personals)
RETURN  device,object,objects,personals",
"x":486,"y":792,"wires":[["9c63a845.8df84"]]}]

//DEVICE - OBJECT - ACTION
[{"id":"4e20926b.a5a7dc","type":"neo4j","z":"bc9bf4a0.4820e","name":"ONLY_OBJECTS2","url":"http://neo4j:integradora@127.0.0.1:7474","query":"MATCH (object{code:{code}})-[:HAVE]->(action) MATCH (object{code:{code}})<-[:HAVE]-(device) RETURN  device,object,action","x":486,"y":792,"wires":[["9c63a845.8df84"]]}]

[{"id":"3509816a.e0ecce","type":"neo4j","z":"bc9bf4a0.4820e","name":"ONLY OBJECTS","url":"http://neo4j:integradora@127.0.0.1:7474","query":"MATCH (device{code:{code}})-[:HAVE]->(object)<-[:link]->(objects)RETURN  object, objects","x":472,"y":1015,"wires":[["fd66356c.7ab8b8"]]}]

// DEVICE - OBJECTS
[{"id":"3509816a.e0ecce","type":"neo4j","z":"bc9bf4a0.4820e","name":"DEVICE_OBJECTS","url":"http://neo4j:integradora@127.0.0.1:7474","query":"MATCH (device{code:{code}})-[:HAVE]->(object)<-[:link]->(objects) RETURN  {object: object, Objects: objects} as objetos","x":472,"y":1015,"wires":[["fd66356c.7ab8b8"]]}]
MATCH (device{code:"000011"})-[:HAVE]->(object)<-[:link]->(objects) RETURN  {object: object, Objects: objects} as objetos

// ACTION(ID,STATUS) -> OBJECTS
[{"id":"3509816a.e0ecce","type":"neo4j","z":"bc9bf4a0.4820e","name":"DEVICE_OBJECTS","url":"http://neo4j:integradora@127.0.0.1:7474","query":"MATCH (device{code:{code},Status:{status}})<-[:HAVE]-(object)-[:link]->(objects) RETURN  {object: object,objects: objects}","x":472,"y":1015,"wires":[["fd66356c.7ab8b8"]]}]
MATCH (device{code:"000017",Status:"ON"})<-[:HAVE]-(object)-[:link]->(objects)
RETURN  {object: object,objects: objects}

// ACTION -> CHANGES ACTIONS
[{"id":"3509816a.e0ecce","type":"neo4j","z":"bc9bf4a0.4820e","name":"UPDATE_ACTIONS","url":"http://neo4j:integradora@127.0.0.1:7474", "query":"MATCH (action {code:{code}})<-[:HAVE]-(object)-[:link]->(objects)-[:HAVE]->(actions) SET action.Status = {status}, actions.Status = {status} RETURN  object, objects, action,actions",  "x":472,"y":1015,"wires":[["fd66356c.7ab8b8"]]}]
MATCH (action {code:"000017"})<-[:HAVE]-(object)-[:link]->(objects)-[:HAVE]->(actions)
SET action.Status = "ON", actions.Status = "ON"
RETURN  object, objects, action,actions
	si retorna 0 rows realizar lo siguiente
	MATCH (action {code:"000017"})
	SET action.Status = "ON"
	RETURN action
