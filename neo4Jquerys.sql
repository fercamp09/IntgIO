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
match(device {code:'000060'})-[:HAVE]->(object)-[:HAVE]->(action)
return device,object,action
