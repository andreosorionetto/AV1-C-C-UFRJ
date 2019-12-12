import matplotlib.pyplot as plt

#          PROJETO 3 TMAB
#Andre Osorio Magaldi Netto                118041914
#Joao Paulo Alves Loureiro Da Silva        117196504
#Rodrigo Bagdadi Benoliel                  118031529


import mysql.connector
import datetime



#Neste código, ficam todas funções utilizadas no app.
#conectando com o banco mysql
mydb = mysql.connector.connect( host = "127.0.0.1", user = "root", 
                               password = "12345678", database = 'esquemagerenciadordelojas' ) 

if(mydb):
    print("Conexão com o banco bem sucedida!")
else:
    print("Erro na conexão com o banco!")
       
mycursor = mydb.cursor()   
   
def inserirLoja(idLoja, categoria, nome, endereco, telefones, x, y):
    try:
        query = """INSERT INTO Lojas VALUES ( """  + str(idLoja) +', "' + categoria + '","' + nome +' "," ' + endereco + ' ",  '+  telefones +'  , ' + str(x) +',' + str(y) + ') ' 
        mycursor.execute(query)
        mydb.commit()
        return True
    except:
        print("Erro ao inserir loja, verifique se este id ja existe!")
        return False

def inserirCliente(idCliente, email, nome, genero):
    try:
        query = """INSERT INTO Clientes VALUES ( """  + str(idCliente) +', "'+  email + '","' + nome + '","' + genero +' ") ' 
        mycursor.execute(query)
        mydb.commit()
        return True
    except:
        print("Erro ao inserir cliente, verifique se o id ja existe!")
        return False

def inserirProduto(idProduto, descricao, nome):
    try:
        query = "INSERT INTO Produtos VALUES ( "  + str(idProduto) +', "'+  descricao + '","' + nome +  '") ' 
        mycursor.execute(query)
        mydb.commit()
        return True
    except:
        print("Erro ao inserir produto, verifique se o id ja existe!")
        return False
     
def inserirEmLoja(idProduto, idLoja, quantidade, preco):
    try:
        query = "INSERT INTO Possui VALUES ( "  + str(idProduto) + ',' + str(idLoja) +  ',' +  str(quantidade) + ',' + str(preco) +  ') ' 
        mycursor.execute(query)
        mydb.commit()
        return True
    except:
        print("Erro ao inserir produto na loja, verifique se o id do produto existe ou se ele ja nao esta nessa loja!")
        return False
        
def inserirCompra(idProduto,idLoja,idCliente,quantidade,dia = datetime.datetime.now() ):
    """ idProduto, idLoja,idCliente, quantidade, datetime"""
    try:
        verif = "select quantidade from possui where Lojas_idLojas = " + idLojas + " and Produtos_idProdutos = " + idProdutos
        mycursor.execute(verif)
        resultado = mycursor.fetchall()[0][0]
        if resultado >= quantidade:
            query = "INSERT INTO Compra VALUES ( "  + str(idProduto) + ',' + str(idLoja) +  ','+ str(idCliente) + ',' +  str(quantidade) + ',"' + str(dia) +  '") '
            mycursor.execute(query)
            mydb.commit()
            upd = "update possui set quantidade = quantidade - " + str(quantidade) + " where Lojas_idLojas = " + str(idLoja) + "and Produtos_idProdutos = " + str(idProduto)
            mycursor.execute(query)
            mydb.commit()
        else:
            print("A loja não possui essa quantidade desse produto em estoque!")
        return True
    except:
        print("Erro ao inserir nova compra!")
        return False
    
def deletarLinha(tabela,idt):
    try:
        query = "delete from "+ tabela +" where id"+tabela+" = "+str(idt) +";"
        print(query)
        mycursor.execute(query)
        mydb.commit()
        return True
    except:
        print("Erro ao deletar linha!")
        return False
    
def reabastecerProduto(idProduto,idLoja,quantidade):
#    try:
        upd = "update possui set quantidade = quantidade + " + str(quantidade) + " where Lojas_idLojas = " + str(idLoja) + " and Produtos_idProdutos = " + str(idProduto)
     
        mycursor.execute(upd)
        mydb.commit()
        return True
#    except:
        print("Erro ao reabastecer produto!")
        return False
    
def top10Produtos():  #Top 10 produtos mais vendidos
    try:
        query = """ SELECT   `Produtos_idProdutos`
                    FROM     `Compra`
                    GROUP BY `Produtos_idProdutos`
                    ORDER BY SUM(Compra.`quantidade`) DESC
                    LIMIT    10; """
            
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
        
def lojasMaisVendedoras():
    try:
        query = """ select Lojas_idLojas
                    FROM     `Compra`
                    GROUP BY `Lojas_idLojas`
                    ORDER BY SUM(Compra.`quantidade`)  DESC
                    LIMIT    5;"""
            
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
        
def lojasQueMaisFaturam():
    try:
        query = """ select  possui.Lojas_idLojas, sum(preço*compra.quantidade) as f  from compra
                    join possui on  possui.`Lojas_idLojas` = compra.`Lojas_idLojas` and possui.`Produtos_idProdutos`  = compra.`Produtos_idProdutos`
                    group by Lojas_idLojas
                    order by f desc
                    limit 5;"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
    
def quantidadeDeProdutos(idLoja):
    try:
        query = """ SELECT	count(Produtos_idProdutos)  
                    FROM	`Possui`
                    WHERE	`Lojas_idLojas` = """ + str(idLoja)
            
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
    
def quantidadeDeLojasPorCategoria():
    try:
        query = """ select	categoria, count(categoria)  
                    from Lojas
                    group by categoria"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
        
def produtoQueMaisVendePorDiaDaSemana(diaDaSemana):
    try:
        query =  """select sum(quantidade) as p
                    from compra
                    where dayname(dia) = 'Monday'
                    group by Produtos_idProdutos
                    order by p desc
                    limit 1"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
    
def disponibilidadeDeProdutoPorQuantidade(idProduto):
    try:
        query =  """select idLojas, lojas.nome, `endereço`, telefone, preço quantidade
                    from lojas inner join possui on lojas.idLojas = possui.Lojas_idLojas
                    where possui.Produtos_idProdutos = """+str(idProduto)+"""
                    order by quantidade desc"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
    
def disponibilidadeDeProdutoPorDistancia(idProduto):
    try:
        query =  """select idLojas, lojas.nome, `endereço`, telefone, preço, sqrt(pow(x,2)+pow(y,2)) as d
                    from lojas inner join possui on lojas.idLojas = possui.Lojas_idLojas
                    where possui.Produtos_idProdutos = """+str(idProduto)+"""
                    order by d desc"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        return True
    except:
        print("Erro ao executar comando!")
        return False
    
def mostraMapa():
    font = {'family': 'serif',
        'color':  'black',
        'weight': 'normal',
        'size': 10} 
    try:
        query =  """select nome, x, y
                    from lojas"""
        mycursor.execute(query)
        rows = mycursor.fetchall()
        mostraBonito(rows)
        print(rows)
        
        figure1=plt.figure(1)
        figure1.suptitle(''' MAPA DAS LOJAS''', fontdict = font)
        subplot1 = figure1.add_subplot(111)
    
        for row in rows:
            plt.scatter( row[1],row[2], c="g" )
            plt.annotate( row[0], (row[1],row[2]) ) 
        
        plt.show()
        return True
    
    except:
        
        print("Erro ao executar comando!")
        return False
    
def mostraBonito(a):
    for i in a:
        print(i)