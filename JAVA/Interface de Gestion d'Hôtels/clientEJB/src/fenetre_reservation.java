import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.swing.*;

import entities.Reservation;
import session.IhotelRemote;

public class fenetre_reservation extends JFrame{
	public JFrame frame;
	public fenetre_reservation() {
		frame = new JFrame();
		
		JLabel txt_titre = new JLabel("Gestion Reservation");
		JLabel txt_id_reservation = new JLabel("ID Reservation");
		JLabel txt_nom_client = new JLabel("Nom Client");
		JLabel txt_prenom_client = new JLabel("Prénom Client");
		JLabel txt_date_debut_r = new JLabel("Date Début Réservation");
		JLabel txt_date_fin_r = new JLabel("Date Fin Réservation");
		
		JTextField id_reservation = new JTextField();
	    JTextField nom_client = new JTextField();
	    JTextField prenom_client = new JTextField();
	    JTextField date_debut_r = new JTextField();
	    JTextField date_fin_r = new JTextField();
	    
		JButton btn_ajouter_reservation = new JButton("Ajouter");
		JButton btn_supprimer_reservation = new JButton("Supprimer");
		JButton btn_quitter = new JButton("Quitter");
		
		txt_titre.setBounds(200,10,150,50);
		
		txt_id_reservation.setBounds(50,100,150,20);
		txt_nom_client.setBounds(50,150,150,20);
		txt_prenom_client.setBounds(50,200,150,20);
		txt_date_debut_r.setBounds(50,250,200,20);
		txt_date_fin_r.setBounds(50,300,200,20);
		
		id_reservation.setBounds(300,100,150,20);
		nom_client.setBounds(300,150,150,20);
		prenom_client.setBounds(300,200,150,20);
		date_debut_r.setBounds(300,250,150,20);
		date_fin_r.setBounds(300,300,150,20);
		
		btn_ajouter_reservation.setBounds(125,400,100,30);
		btn_supprimer_reservation.setBounds(250,400,150,30);
		btn_quitter.setBounds(125,450,100,30);
		
		
		frame.add(txt_titre);
		
		frame.add(txt_id_reservation);
		frame.add(id_reservation);
		
		frame.add(txt_nom_client);
		frame.add(nom_client);
		
		frame.add(txt_prenom_client);
		frame.add(prenom_client);
		
		frame.add(txt_date_debut_r);
		frame.add(date_debut_r);
		
		frame.add(txt_date_fin_r);
		frame.add(date_fin_r);
		
		frame.add(btn_ajouter_reservation);
		frame.add(btn_supprimer_reservation);
		frame.add(btn_quitter);
		
		frame.setTitle("Gestion des Hôtels --- Réservation");
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
					stub.addreservation(new Reservation(nom_client.getText(), prenom_client.getText(), Long.parseLong(date_debut_r.getText()), Long.parseLong(date_fin_r.getText())));
					nom_client.setText("");
					prenom_client.setText("");
					date_debut_r.setText("");
					date_fin_r.setText("");
				}
			};
			btn_ajouter_reservation.addActionListener(EcouteurB18);
			
			ActionListener EcouteurB19 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(id_reservation.getText());
					stub.deletereservation(a);
				}
			};
			btn_supprimer_reservation.addActionListener(EcouteurB19);
			
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
	    new fenetre_reservation();
	}
}