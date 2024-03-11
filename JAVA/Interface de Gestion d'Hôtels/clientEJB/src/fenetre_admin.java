import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.swing.*;

import entities.Administrateur;
import session.IhotelRemote;

public class fenetre_admin extends JFrame{
	public JFrame frame;
	public fenetre_admin() {
		frame = new JFrame();
		
		JLabel txt_titre = new JLabel("Gestion Administrateur");
		JLabel txt_id_admin = new JLabel("ID Admin");
		JLabel txt_nom_admin = new JLabel("Nom Admin");
		JLabel txt_prenom_admin = new JLabel("Prénom Admin");
		
		JTextField id_admin = new JTextField();
	    JTextField nom_admin = new JTextField();
	    JTextField prenom_admin = new JTextField();
	    
		JButton btn_ajouter_admin = new JButton("Ajouter");
		JButton btn_supprimer_admin = new JButton("Supprimer");
		JButton btn_quitter = new JButton("Quitter");
		
		txt_titre.setBounds(175,10,200,50);
		
		txt_id_admin.setBounds(50,100,150,20);
		txt_nom_admin.setBounds(50,150,150,20);
		txt_prenom_admin.setBounds(50,200,150,20);
		
		id_admin.setBounds(300,100,150,20);
		nom_admin.setBounds(300,150,150,20);
		prenom_admin.setBounds(300,200,150,20);
		
		btn_ajouter_admin.setBounds(100,275,100,30);
		btn_supprimer_admin.setBounds(250,275,125,30);
		btn_quitter.setBounds(100,325,100,30);
		
		
		frame.add(txt_titre);
		
		frame.add(txt_id_admin);
		frame.add(id_admin);
		
		frame.add(txt_nom_admin);
		frame.add(nom_admin);
		
		frame.add(txt_prenom_admin);
		frame.add(prenom_admin);
		
		frame.add(btn_ajouter_admin);
		frame.add(btn_supprimer_admin);
		frame.add(btn_quitter);
		
		frame.setTitle("Gestion des Hôtels --- Administrateur");
	    frame.setLayout(null);
		frame.setSize(500,425);
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
			ActionListener EcouteurB12 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					stub.addadmin(new Administrateur(nom_admin.getText(), prenom_admin.getText()));
					nom_admin.setText("");
					prenom_admin.setText("");
				}
			};
			btn_ajouter_admin.addActionListener(EcouteurB12);
			
			ActionListener EcouteurB13 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(id_admin.getText());
					stub.deleteadmin(a);
				}
			};
			btn_supprimer_admin.addActionListener(EcouteurB13);
			
			ActionListener EcouteurB14 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					System.exit(0);
				}
			};
			btn_quitter.addActionListener(EcouteurB14);
		}
		
		catch (NamingException e) {
			e.printStackTrace();
		}         
	}
	
	public static void main(String[] args) {
	    new fenetre_admin();
	}
}