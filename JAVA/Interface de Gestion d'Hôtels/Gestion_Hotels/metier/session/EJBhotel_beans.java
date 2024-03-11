package session;

import entities.Administrateur;
import entities.Adresse;
import entities.Chambre;
import entities.Client;
import entities.Hotel;
import entities.Reservation;

import java.util.*;

import javax.ejb.*;
import javax.persistence.*;


@Stateless
public class EJBhotel_beans implements IhotelLocal, IhotelRemote{
	@PersistenceContext (name="TEST_UP_hotels")
	
	private EntityManager man;
	
	@Override
	public void addhotel(Hotel H) {
		man.persist(H);
	}
	
	@Override
	public void deletehotel(Long Code) {
		Hotel h = man.find(Hotel.class, Code);
		man.remove(h);
	}
	
	@Override
	public Hotel rechercher(Long Code) {
		Hotel H = man.find(Hotel.class, Code);
		if (H == null) throw new RuntimeException("Hotel Introuvable");
		return H;
	}
	
	@Override
	public void updatehotel(Hotel H) {
		man.merge(H);
	}
	
	@Override
	public List<Hotel> getlist_hotel() {
		Query req = man.createQuery("Select H from Hotel H ");
		
		return req.getResultList();
	}
	
	public List findwithName (String name) {
		return man.createQuery(
				"SELECT c FROM Client c WHERE c.name LIKE :nom_client")
				.setParameter("nom_client", name)
				.setMaxResults(10)
				.getResultList();
	}
	
	@Override
	public void addclient(Client C) {
		man.persist(C);
	}
	
	@Override
	public void deleteclient(Long ID) {
		Client c = man.find(Client.class, ID);
		man.remove(c);
	}
	
	@Override
	public Client rechercher_c(Long Code) {
		Client C = man.find(Client.class, Code);
		if (C == null) throw new RuntimeException("Client Introuvable");
		return C;
	}
	
	@Override
	public void updateclient(Client C) {
		man.merge(C);
	}
	
	@Override
	public void addadmin(Administrateur A) {
		man.persist(A);
	}
	
	@Override
	public void deleteadmin(Long ID) {
		Administrateur a = man.find(Administrateur.class, ID);
		man.remove(a);
	}
	
	@Override
	public Administrateur rechercher_a(Long Code) {
		Administrateur A = man.find(Administrateur.class, Code);
		if (A == null) throw new RuntimeException("Admin Introuvable");
		return A;
	}
	
	@Override
	public void updateadmin(Administrateur A) {
		man.merge(A);
	}
	
	@Override
	public void addadr(Adresse Ad) {
		man.persist(Ad);
	}
	
	@Override
	public void deleteadr(Long ID) {
		Adresse ad = man.find(Adresse.class, ID);
		man.remove(ad);
	}
	
	@Override
	public Adresse rechercher_adr(Long Code) {
		Adresse Ad = man.find(Adresse.class, Code);
		if (Ad == null) throw new RuntimeException("Adresse Introuvable");
		return Ad;
	}
	
	@Override
	public void updateadr(Adresse Ad) {
		man.merge(Ad);
	}
	
	@Override
	public void addcham(Chambre Ch) {
		man.persist(Ch);
	}
	
	@Override
	public void deletecham(Long ID) {
		Chambre ch = man.find(Chambre.class, ID);
		man.remove(ch);
	}
	
	@Override
	public Chambre rechercher_cham(Long Code) {
		Chambre Ch = man.find(Chambre.class, Code);
		if (Ch == null) throw new RuntimeException("Chambre Introuvable");
		return Ch;
	}
	
	@Override
	public void updatecham(Chambre Ch) {
		man.merge(Ch);
	}
	
	@Override
	public void addreservation(Reservation R) {
		man.persist(R);
	}
	
	@Override
	public void deletereservation(Long ID) {
		Reservation r = man.find(Reservation.class, ID);
		man.remove(r);
	}
	
	@Override
	public Reservation rechercher_reservation(Long Code) {
		Reservation R = man.find(Reservation.class, Code);
		if (R == null) throw new RuntimeException("Reservation Introuvable");
		return R;
	}
	
	@Override
	public void updatereservation(Reservation R) {
		man.merge(R);
	}

}
