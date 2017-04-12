#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
#Bibliotecas
import time
import serial
import datetime
from apscheduler.schedulers.blocking import BlockingScheduler


def aquisicao():
	# Iniciando conexao serial
	comport = serial.Serial('/dev/ttyUSB0', 9600)


	VALUE_SERIAL=comport.readline()


	print '\nRetorno da serial: %s' % (VALUE_SERIAL)

	print 'Enviando comando...'

	PARAM_CARACTER='l'

    # Enviando 'l'
	comport.write(PARAM_CARACTER)

	print 'Comando enviado!'

	# Lendo mensagem recebida após envio de 'l'
	VALUE_SERIAL=comport.readline()


	print '\nValores: %s' % (VALUE_SERIAL)

	# Fechando conexao serial
	comport.close()

	# Retornando mensagem recebida
	return VALUE_SERIAL


def escrever_arquivo(BUFFER):
	# Abre arquivo no modo "adicionar" 
	f = open('log.dat','a')
	f.write(BUFFER)
	f.write('\n')
	f.close()
	return

def some_job():
	valor = aquisicao()
	hora = datetime.datetime.now().time()
	print hora
	string_hora = str(hora)
	string_hora = string_hora[0:8]
	aux = string_hora + '\t' + str(valor)
	escrever_arquivo(aux)
	return


# Começando o main aqui
f = open('log.dat','w')
f.close()

scheduler = BlockingScheduler()
#scheduler.add_job(some_job, 'interval', hours=1)
#Executando a cada 30 minutos
scheduler.add_job(some_job, 'interval', minutes=30)
#scheduler.add_job(some_job, 'interval', seconds=5)
scheduler.start()












