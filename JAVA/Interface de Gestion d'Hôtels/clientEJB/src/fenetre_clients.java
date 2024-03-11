import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.swing.*;

import entities.Client;
import entities.Hotel;
import session.IhotelRemote;

public class fenetre_clients extends JFrame{
	public JFrame frame;
	public fenetre_clients() {
		frame = new JFrame();
		
		JLabel txt_titre = new JLabel("Gestion Client");
		JLabel txt_id_client = new JLabel("ID Client");
		JLabel txt_nom_client = new JLabel("Nom Client");
		JLabel txt_prenom_client = new JLabel("Prénom Client");
		JLabel txt_numero_tel_client = new JLabel("Téléphone Client");
		
		JTextField id_client = new JTextField();
	    JTextField nom_client = new JTextField();
	    JTextField prenom_client = new JTextField();
	    JTextField numero_tel_client = new JTextField();
	    
		JButton btn_ajouter_client = new JButton("Ajouter");
		JButton btn_supprimer_client = new JButton("Supprimer");
		JButton btn_quitter = new JButton("Quitter");
		
		txt_titre.setBounds(200,10,150,50);
		
		txt_id_client.setBounds(50,100,150,20);
		txt_nom_client.setBounds(50,150,150,20);
		txt_prenom_client.setBounds(50,200,150,20);
		txt_numero_tel_client.setBounds(50,250,200,20);
		
		id_client.setBounds(300,100,150,20);
		nom_client.setBounds(300,150,150,20);
		prenom_client.setBounds(300,200,150,20);
		numero_tel_client.setBounds(300,250,150,20);
		
		btn_ajouter_client.setBounds(100,350,100,30);
		btn_supprimer_client.setBounds(250,350,125,30);
		btn_quitter.setBounds(100,400,100,30);
		
		
		frame.add(txt_titre);
		
		frame.add(txt_id_client);
		frame.add(id_client);
		
		frame.add(txt_nom_client);
		frame.add(nom_client);
		
		frame.add(txt_prenom_client);
		frame.add(prenom_client);
		
		frame.add(txt_numero_tel_client);
		frame.add(numero_tel_client);
		
		
		frame.add(btn_ajouter_client);
		frame.add(btn_supprimer_client);
		frame.add(btn_quitter);
		
		frame.setTitle("Gestion des Hôtels --- Client");
	    frame.setLayout(null);
		frame.setSize(500,500);
		frame.setVisible(true);
		
		try {
			Properties p = new Properties();
            p.put(Context.INITIAL_CONTEXT_FACTORY, "org.wildfly.naming.client.WildFlyInitialContextFactory");
            p.put(Context.URL_PKG_PREFIXES, "org.wildfly.naming.client.WildFlyInitialContextFactory");
            p.put(Context.PROVIDER_URL, "http-remoting://127.0.0.1:8080/");
            p.put("jboss.naming.client.ejb.context", true);
            p.put("org.jboss.ejb.client.scoped.context", "true");
            Context ctx = new InitialContext(p);
            
            final IhotelRemote stub = (IhotelRemote) ctx.lookup("Gestion_Hotels/EJBhotel_beans!session.IhotelRemote");
            
          //AJOUTER*
			ActionListener EcouteurB8 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					stub.addclient(new Client(nom_client.getText(), prenom_client.getText(), Long.parseLong(numero_tel_client.getText())));
					nom_client.setText("");
					prenom_client.setText("");
					numero_tel_client.setText("");
				}
			};
			btn_ajouter_client.addActionListener(EcouteurB8);
			
			ActionListener EcouteurB9 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(id_client.getText());
					stub.deleteclient(a);
				}
			};
			btn_supprimer_client.addActionListener(EcouteurB9);
			
			ActionListener EcouteurB10 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					System.exit(0);
				}
			};
			btn_quitter.addActionListener(EcouteurB10);
		}
		
		catch (NamingException e) {
			e.printStackTrace();
		}         
	}
	
	public static void main(String[] args) {
	    new fenetre_clients();
	}
}