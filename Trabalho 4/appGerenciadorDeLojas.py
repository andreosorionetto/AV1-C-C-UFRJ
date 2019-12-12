
#          PROJETO 3 TMAB
#Andre Osorio Magaldi Netto                118041914
#Joao Paulo Alves Loureiro Da Silva        117196504
#Rodrigo Bagdadi Benoliel                  118031529


from funçõesGerenciadorDeLojas import *

#Neste código fica a interface do app de gerenciamento de lojas.
#Nós importamos o arquivo com as funçoes necessarias para fazer as consultas no banco de dados.
    
def interface():
    while True:
        print('SISTEMA DE GERENCIAMENTO DE LOJAS')
        print('Escolha qual comando deseja realizar:')
        print('1: Registrar nova loja.')   #ok
        print('2: Registrar novo cliente.')   #ok
        print('3: Registrar novo produto.')   #ok
        print('4: Adicionar produto registrado ao catálogo de uma loja.')   #ok
        print('5: Registrar nova compra.')
        print('6: Apagar do registro uma loja.')   
        print('7: Apagar do registro um cliente.')
        print('8: Apagar do registro um produto.')
        print('9: Abastecer o estoque de uma loja.')
        print('10: Ver os 10 produtos mais vendidos.')
        print('11: Ver as 5 lojas que mais vendem.')
        print('12: Ver as 5 lojas que mais faturam.')
        print('13: Ver a quantidade de produtos de uma loja.')
        print('14: Ver a quantidade de lojas por categoria.')
        print('15: Ver qual produto é o mais vendido por dia da semana.')
        print('16: Consultar a disponibilidade de produtos por quantidade.')
        print('17: Consultar a disponibilidade de produtos por distância.')
        print('18: Mostrar mapa com lojas e finalizar.')
        print('Ou digite "sair" para finalizar agora. \n')
        escolha = input()
        try:
            if escolha == 'sair':
                return None
            elif int(escolha) in range(19)[1:]:
                break
            
        except:
            print("Digite o número da opção!")
    print('(Para voltar para o menu principal, aperte enter sem inserir nada)')
            
    if escolha == '1':
        print('Insira respectivamente: (idLoja,categoria,nome,endereço,telefones,x,y) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        print(args)
        print(int(args[-3]))
        if inserirLoja(int(args[0]), args[1], args[2], args[3], (args[4]), int(args[5]), int(args[6])):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
        
    elif escolha == '2':
        print('Insira respectivamente: (idCliente,email,nome,genero) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        if inserirCliente(int(args[0]), args[1], args[2], args[3]):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '3':
        print('Insira respectivamente: (idProduto,descricao,nome) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        if inserirProduto(int(args[0]), args[1], args[2]):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '4':
        print('Insira respectivamente: (idProduto,idLoja,quantidade,preco) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        if inserirEmLoja(int(args[0]), int(args[1]), int(args[2]), float(args[3])):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '5':
        print('Insira respectivamente: (idProduto,idLoja,idCliente,quantidade) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        if inserirCompra(int(args[0]), int(args[1]), args[2], args[3], dia = datetime.datetime.now()):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '6':
        print('Insira: (idLoja) \n')
        args = input()
        if args  == '':
            interface()
            return None
        if deletarLinha('Lojas',args):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '7':
        print('Insira: (idCliente) \n')
        args = input()
        if args  == '':
            interface()
            return None
        if deletarLinha('Clientes',args):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    elif escolha == '8':
        print('Insira: (idProduto) \n')
        args = input()
        if args  == '':
            interface()
            return None
        if deletarLinha('Produtos',args):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '9':
        print('Insira: (idProduto,idLoja,quantidade) \n')
        args = input()
        if args  == '':
            interface()
            return None
        args = args.split(',')
        if reabastecerProduto(int(args[0]),int(args[1]),int(args[2])):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '10':
        print('(idProduto)')
        if top10Produtos():  
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '11':
        print('(idLojas)')
        if lojasMaisVendedoras():
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '12':
        print('(idLojas)')
        if lojasQueMaisFaturam():
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '13':
        print('Insira: (idLoja) \n')
        args = input()
        print('(Quantidade)')
        if args  == '':
            interface()
            return None
        if quantidadeDeProdutos(int(args)):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '14':
        print('(Categoria, quantidade)')
        if quantidadeDeLojasPorCategoria():
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '15':
        print('Insira: (dia da semana(em inglês)) \n')
        args = input()
        if args  == '':
            interface()
            return None
        print('(idProduto)')
        if produtoQueMaisVendePorDiaDaSemana(args):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '16':
        print('Insira: (idProduto) \n')
        args = input()
        if args  == '':
            interface()
            return None
        print('(IdLoja,Nome,Endereço,Telefone,Quantidade)')
        if disponibilidadeDeProdutoPorQuantidade(int(args)):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '17':
        print('Insira: (idProduto) \n')
        args = input()
        if args  == '':
            interface()
            return None
        print('(IdLoja,Nome,Endereço,Telefone,Distância Euclidiana)')
        if disponibilidadeDeProdutoPorDistancia(int(args)):
            print('Comando realizado com sucesso! Aperte "enter" para voltar ao menu principal ou "sair" para finalizar.')
        if input() == '':
            interface()
        return None
        
    if escolha == '18':
        if mostraMapa():
            print('Comando realizado com sucesso! Volte sempre.')
        else: 
            interface()
        return None
       
interface()

         
        
        



