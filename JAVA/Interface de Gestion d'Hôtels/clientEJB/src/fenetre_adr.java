import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.swing.*;

import entities.Adresse;
import session.IhotelRemote;

public class fenetre_adr extends JFrame{
	public JFrame frame;
	public fenetre_adr() {
		frame = new JFrame();
		
		JLabel txt_titre = new JLabel("Gestion Adresse");
		JLabel txt_id_adr = new JLabel("ID Adresse");
		JLabel txt_n_rue = new JLabel("N° Rue");
		JLabel txt_rue = new JLabel("Rue");
		JLabel txt_ville = new JLabel("Ville");
		JLabel txt_code_postal = new JLabel("Code Postal");
		JLabel txt_region = new JLabel("Région");
		
		JTextField id_adr = new JTextField();
	    JTextField n_rue = new JTextField();
	    JTextField rue = new JTextField();
	    JTextField ville = new JTextField();
	    JTextField code_postal = new JTextField();
	    JTextField region = new JTextField();
	    
		JButton btn_ajouter_adr = new JButton("Ajouter");
		JButton btn_supprimer_adr = new JButton("Supprimer");
		JButton btn_quitter = new JButton("Quitter");
		
		txt_titre.setBounds(200,10,150,50);
		
		txt_id_adr.setBounds(50,100,150,20);
		txt_n_rue.setBounds(50,150,150,20);
		txt_rue.setBounds(50,200,150,20);
		txt_ville.setBounds(50,250,150,20);
		txt_code_postal.setBounds(50,300,150,20);
		txt_region.setBounds(50,350,150,20);
		
		id_adr.setBounds(250,100,200,20);
		n_rue.setBounds(250,150,200,20);
		rue.setBounds(250,200,200,20);
		ville.setBounds(250,250,200,20);
		code_postal.setBounds(250,300,200,20);
		region.setBounds(250,350,200,20);
		
		
		btn_ajouter_adr.setBounds(100,450,100,30);
		btn_supprimer_adr.setBounds(250,450,125,30);
		btn_quitter.setBounds(100,500,100,30);
		
		
		frame.add(txt_titre);
		
		frame.add(txt_id_adr);
		frame.add(id_adr);
		
		frame.add(txt_n_rue);
		frame.add(n_rue);
		
		frame.add(txt_rue);
		frame.add(rue);
		
		frame.add(txt_ville);
		frame.add(ville);
		
		frame.add(txt_code_postal);
		frame.add(code_postal);
		
		frame.add(txt_region);
		frame.add(region);
		
		frame.add(btn_ajouter_adr);
		frame.add(btn_supprimer_adr);
		frame.add(btn_quitter);
		
		frame.setTitle("Gestion des Hôtels --- Adresse");
	    frame.setLayout(null);
		frame.setSize(500,600);
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
			ActionListener EcouteurB15 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					stub.addadr(new Adresse(Integer.parseInt(n_rue.getText()), rue.getText(), ville.getText(), Long.parseLong(code_postal.getText()), region.getText()));
					n_rue.setText("");
					rue.setText("");
					ville.setText("");
					code_postal.setText("");
					region.setText("");
				}
			};
			btn_ajouter_adr.addActionListener(EcouteurB15);
			
			ActionListener EcouteurB16 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(id_adr.getText());
					stub.deleteadr(a);
				}
			};
			btn_supprimer_adr.addActionListener(EcouteurB16);
			
			ActionListener EcouteurB17 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					System.exit(0);
				}
			};
			btn_quitter.addActionListener(EcouteurB17);
		}
		
		catch (NamingException e) {
			e.printStackTrace();
		}         
	}
	
	public static void main(String[] args) {
	    new fenetre_adr();
	}
}