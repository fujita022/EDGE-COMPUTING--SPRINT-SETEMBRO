O projeto proposto foi um projeto onde está um sistema de segurança conectado à um ambiente com alarme, sensor de movimento, e luminosidade, onde quando acionados ele dispará avisará que tem movimentos indevidos no local.
O projeto estará conectado a uma rede WiFi e ao servidor MQTT, onde por dispositivos móveis será possível ver o progresso.
Dessa forma, simulando uma ação, a luminosidade do local por padrão escuro será luz baixa, caso haja qualquer tipo de luz, será mudada para a luz ambiente e caso a luz acesa, um aviso de luz clara.
O projeto foi desenvolvido com o objetivo de criar um sistema de segurança inteligente que pode definir quando há movimentações estranhas e mandar diretamente a mensagem por WiFi, sendo conectado a um servidor.

Quando o servidor e o WiFi estiverem conectados será aceso LEDs que confirmam isso (LED VERDE = WIFI && LED AMARELO = SERVIDOR MQTT.)

Para o projeto ser concluído com êxito é necessário conectar-se à rede WiFi necessária, e ao servidor MQTT. Instalar a biblioteca PubSubclient, e Wifi.H, que dessa forma ela fará as requisições automáticas necessárias.
