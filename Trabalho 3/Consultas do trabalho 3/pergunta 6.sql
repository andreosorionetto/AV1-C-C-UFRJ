SELECT Carro_Renavam, Validade, `Clientes_id Cliente`
FROM `faz parte`
INNER JOIN carro ON carro.Renavam = `faz parte`.Carro_Renavam
INNER JOIN contrato ON contrato.`id Contrato` = `faz parte`.`Contrato_id Contrato`
INNER JOIN `é contraparte` ON contrato.`id Contrato` = `é contraparte`.`Contrato_id Contrato`
WHERE Validade > curdate()
ORDER BY `Preço` DESC 