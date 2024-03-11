import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;

import javax.naming.*;
import javax.swing.*;

import entities.Hotel;
import session.IhotelRemote;

public class fenetres extends JFrame{
	public JFrame frame;
	public fenetres() {
		frame = new JFrame();
		
		JTextArea affiche_hotel_jtextarea = new JTextArea("Résultat de la Consultation d'Hôtels", 20,20);
		
        JTextField textfield_txt_cd = new JTextField();
        JTextField textfield_txt_nom  = new JTextField();
        JTextField textfield_txt_nb_e = new JTextField();

        JLabel txt_titre = new JLabel("Gestion des Hotels");
        JLabel txt_cd = new JLabel("Code_Hotel");
        JLabel txt_nom = new JLabel("Nom");
        JLabel txt_nb_e = new JLabel("Nb_Etoiles");
        
        JButton button_admin = new JButton("Ajouter Administrateur");
        JButton button_adr = new JButton("Ajouter Adresse");
        JButton button_chambre = new JButton("Ajouter Chambre");
        JButton button_client = new JButton("Ajouter Client");
        JButton button_reservation = new JButton("Ajouter Réservation");
        
        JButton button_ajouter = new JButton("Ajouter");
        JButton button_supprimer = new JButton("Supprimer");
        JButton button_quitter = new JButton("Quitter");
        JButton button_consulter = new JButton("Consulter");
        
		JRadioButton consulter_hotel = new JRadioButton("Consulter Hotels");
        JRadioButton consulter_hotel_par_code = new JRadioButton("Consulter par Code Hotel");
    
        button_admin.setBounds(10, 250, 550, 30);
        button_adr.setBounds(10, 300, 550, 30);
        button_chambre.setBounds(10, 350, 550, 30);
        button_client.setBounds(10, 400, 550, 30);
        button_reservation.setBounds(10, 450, 550, 30);
        
        button_ajouter.setBounds(400, 60, 120, 30);
        button_supprimer.setBounds(400, 110, 120, 30);
        button_quitter.setBounds(400, 160, 120, 30);
        button_consulter.setBounds(600, 60,120, 30);
        
        consulter_hotel.setBounds(600, 110, 150, 30);
        consulter_hotel_par_code.setBounds(600, 140, 250, 30);
        
        txt_titre.setBounds(200, 10, 200, 30);
        txt_cd.setBounds(20, 60, 120, 30);
        txt_nom.setBounds(20, 110, 120, 30);
        txt_nb_e.setBounds(20, 160,120, 30);
        
        textfield_txt_cd.setBounds(150, 60, 170, 30);
        textfield_txt_nom.setBounds(150, 110, 170, 30);
        textfield_txt_nb_e.setBounds(150, 160,170, 30);
        
        affiche_hotel_jtextarea.setBounds(600,200,275,300);
        
        frame.add(textfield_txt_cd);
        frame.add(textfield_txt_nb_e);
        frame.add(textfield_txt_nom);
        
        frame.add(txt_titre);
        frame.add(txt_cd);
        frame.add(txt_nb_e);
        frame.add(txt_nom);

        frame.add(button_admin);
        frame.add(button_adr);
        frame.add(button_chambre);
        frame.add(button_client);
        frame.add(button_reservation);
        
        frame.add(button_ajouter);
        frame.add(button_supprimer);
        frame.add(button_quitter);
        frame.add(button_consulter);
        
        frame.add(consulter_hotel);
        frame.add(consulter_hotel_par_code);
		
		frame.setTitle("Gestion des Hotels");
		frame.setSize(900,600); 
		frame.setLayout(null);
		frame.setVisible(true);
		
		frame.add(affiche_hotel_jtextarea);
		
		try {
			Properties p = new Properties();
            p.put(Context.INITIAL_CONTEXT_FACTORY, "org.wildfly.naming.client.WildFlyInitialContextFactory");
            p.put(Context.URL_PKG_PREFIXES, "org.wildfly.naming.client.WildFlyInitialContextFactory");
            p.put(Context.PROVIDER_URL, "http-remoting://127.0.0.1:8080/");
            p.put("jboss.naming.client.ejb.context", true);
            p.put("org.jboss.ejb.client.scoped.context", "true");
            Context ctx = new InitialContext(p);
            
            final IhotelRemote stub = (IhotelRemote) ctx.lookup("Gestion_Hotels/EJBhotel_beans!session.IhotelRemote");


			//CONSULTER*
			/*ActionListener EcouteurB1 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					if (consulter_hotel.isSelected())
					{
						List<Hotel> h = stub.getlist_hotel();
						for (int i = 0; i<h.size(); i++)
						textfield_txt_nb_e.setText(textfield_txt_nb_e.getText()+"\n"+h.get(i).getCode_hotel()+"\n"+h.get(i).getNom()+h.get(i).getNb_etoiles());
					}
					
					else if (consulter_hotel_par_code.isSelected() == true)
					{
						Long a = Long.parseLong(textfield_txt_cd.getText());
						Hotel b = stub.rechercher(a);
						textfield_txt_nb_e.setText(textfield_txt_nb_e.getText()+"\n"+b.getCode_hotel()+"\n"+b.getNom()+b.getNb_etoiles());
					}
				}
			};
			button_consulter.addActionListener(EcouteurB1);
			
			ActionListener EcouteurB2 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					textfield_txt_cd.setEnabled(true);
					textfield_txt_nom.setEnabled(false);
					textfield_txt_nb_e.setEnabled(false);
				}
			};
			consulter_hotel_par_code.addActionListener(EcouteurB2);
		
			ActionListener EcouteurB3 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					textfield_txt_cd.setEnabled(false);
					textfield_txt_nom.setEnabled(false);
					textfield_txt_nb_e.setEnabled(false);
					button_ajouter.setEnabled(false);
				}
			};
			consulter_hotel.addActionListener(EcouteurB3);*/
			
			
			//AJOUTER*
			ActionListener EcouteurB4 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					stub.addhotel(new Hotel(textfield_txt_nom.getText(), Integer.parseInt(textfield_txt_nb_e.getText())));
					textfield_txt_cd.setText("");
					textfield_txt_nom.setText("");
					textfield_txt_nb_e.setText("");
				}
			};
			button_ajouter.addActionListener(EcouteurB4);
			
			ActionListener EcouteurB5 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					Long a = Long.parseLong(textfield_txt_cd.getText());
					stub.deletehotel(a);
				}
			};
			button_supprimer.addActionListener(EcouteurB5);
			
			ActionListener EcouteurB6 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					new fenetre_admin();
				}
			};
			button_admin.addActionListener(EcouteurB6);
			
			ActionListener EcouteurB7 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					new fenetre_adr();
				}
			};
			button_adr.addActionListener(EcouteurB7);
			
			ActionListener EcouteurB8 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					new fenetre_chambres();
				}
			};
			button_chambre.addActionListener(EcouteurB8);
			
			ActionListener EcouteurB9 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					new fenetre_clients();
				}
			};
			button_client.addActionListener(EcouteurB9);
			
			ActionListener EcouteurB10 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					new fenetre_reservation();
				}
			};
			button_reservation.addActionListener(EcouteurB10);
			
			ActionListener EcouteurB11 = new ActionListener () 
			{
				public void actionPerformed (ActionEvent e) 
				{
					System.exit(0);
				}
			};
			button_quitter.addActionListener(EcouteurB11);
		}
		
		catch (NamingException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
	    new fenetres();
	}
}