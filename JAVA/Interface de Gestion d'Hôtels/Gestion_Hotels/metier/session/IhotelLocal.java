package session;

import java.util.List;

import entities.Administrateur;
import entities.Adresse;
import entities.Chambre;
import entities.Client;
import entities.Hotel;
import entities.Reservation;

import javax.ejb.Local;

@Local
public interface IhotelLocal {

	void addhotel(Hotel H);

	void deletehotel(Long Code);

	Hotel rechercher(Long Code);

	void updatehotel(Hotel H);

	List<Hotel> getlist_hotel();
	
	void addclient(Client C);

	void deleteclient(Long Code);

	Client rechercher_c(Long Code);

	void updateclient(Client C);
	
	void addadmin(Administrateur A);

	void deleteadmin(Long ID);

	Administrateur rechercher_a(Long Code);

	void updateadmin(Administrateur A);
	
	void addadr(Adresse Ad);

	void deleteadr(Long ID);

	Adresse rechercher_adr(Long Code);

	void updateadr(Adresse Ad);
	
	void addcham(Chambre Ch);

	void deletecham(Long ID);

	Chambre rechercher_cham(Long Code);

	void updatecham(Chambre Ch);
	
	void addreservation(Reservation R);

	void deletereservation(Long ID);

	Reservation rechercher_reservation(Long Code);

	void updatereservation(Reservation R);
}
