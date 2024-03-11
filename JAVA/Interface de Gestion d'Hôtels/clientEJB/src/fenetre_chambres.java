import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.swing.*;

import entities.Chambre;
import session.IhotelRemote;

public class fenetre_chambres extends JFrame{
	public JFrame frame;
	public fenetre_chambres() {
		frame = new JFrame();
		
		JLabel txt_titre = new JLabel("Gestion Chambres");
		JLabel txt_id_chambre = new JLabel("ID Chambres");
		JLabel txt_num_chambre = new JLabel("Numéro Chambre");
		JLabel txt_nb_lits = new JLabel("Nombre Lits");
		JLabel txt_num_cle = new JLabel("Numéro Clé");
		JLabel txt_num_etage = new JLabel("Numéro Étage");
		
		JTextField id_cham = new JTextField();
	    JTextField num_chambre = new JTextField();
	    JTextField nb_lits = new JTextField();
	    JTextField num_cle = new JTextField();
	    JTextField num_etage = new JTextField();
	    
		JButton btn_ajouter_chambre = new JButton("Ajouter");
		JButton btn_supprimer_chambre = new JButton("Supprimer");
		JButton btn_quitter = new JButton("Quitter");
		
		txt_titre.setBounds(200,10,150,50);
		
		txt_id_chambre.setBounds(50,100,150,20);
		txt_num_chambre.setBounds(50,150,150,20);
		txt_nb_lits.setBounds(50,200,150,20);
		txt_num_cle.setBounds(50,250,150,20);
		txt_num_etage.setBounds(50,300,150,20);
		
		id_cham.setBounds(300,100,150,20);
		num_chambre.setBounds(300,150,150,20);
		nb_lits.setBounds(300,200,150,20);
		num_cle.setBounds(300,250,150,20);
		num_etage.setBounds(300,300,150,20);
		
		btn_ajouter_chambre.setBounds(125,400,100,30);
		btn_supprimer_chambre.setBounds(250,400,125,30);
		btn_quitter.setBounds(125,450,100,30);
		
		
		frame.add(txt_titre);
		
		frame.add(txt_id_chambre);
		frame.add(id_cham);
		
		frame.add(txt_num_chambre);
		frame.add(num_chambre);
		
		frame.add(txt_nb_lits);
		frame.add(nb_lits);
		
		frame.add(txt_num_cle);
		frame.add(num_cle);
		
		frame.add(txt_num_etage);
		frame.add(num_etage);
		
		frame.add(btn_ajouter_chambre);
		frame.add(btn_supprimer_chambre);
		frame.add(btn_quitter);
		
		frame.setTitle("Gestion des Hôtels --- Chambres");
	    frame.setLayout(null);
		frame.setSize(525,600);
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
			ActionListener EcouteurB18 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					stub.addcham(new Chambre(Integer.parseInt(num_chambre.getText()), Integer.parseInt(nb_lits.getText()), Integer.parseInt(num_cle.getText()), Integer.parseInt(num_etage.getText())));
					num_chambre.setText("");
					nb_lits.setText("");
					num_cle.setText("");
					num_etage.setText("");
				}
			};
			btn_ajouter_chambre.addActionListener(EcouteurB18);
			
			ActionListener EcouteurB19 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(id_cham.getText());
					stub.deletecham(a);
				}
			};
			btn_supprimer_chambre.addActionListener(EcouteurB19);
			
			ActionListener EcouteurB20 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					System.exit(0);
				}
			};
			btn_quitter.addActionListener(EcouteurB20);
		}
		
		catch (NamingException e) {
			e.printStackTrace();
		}         
	}
	
	public static void main(String[] args) {
	    new fenetre_chambres();
	}
}