package entities;

import java.io.Serializable;

import javax.persistence.*;

@Entity
@Table(name="Adresse")
@Embeddable
public class Adresse implements Serializable{
	@Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    @Column(name="ID_adresse") private long id_adresse;
    @Column(name="n_rue") private int n_rue;
    @Column(name="rue") private String rue;
    @Column(name="ville") private String ville;
    @Column(name="region") private String region;
    @Column(name="code_postal") private long code_postal;
    
    
    @OneToOne
	@JoinColumn(name="ID_adresse") private Hotel hadresse;
    
	public Adresse(int n_rue, String rue, String ville, long code_postal, String region) {
		super();
		this.n_rue = n_rue;
		this.rue = rue;
		this.ville = ville;
		this.region = region;
		this.code_postal = code_postal;
	}


	public Adresse() {
		super();
	}


	public int getN_rue() {
		return n_rue;
	}


	public void setN_rue(int n_rue) {
		this.n_rue = n_rue;
	}


	public String getRue() {
		return rue;
	}


	public void setRue(String rue) {
		this.rue = rue;
	}


	public String getVille() {
		return ville;
	}


	public void setVille(String ville) {
		this.ville = ville;
	}


	public String getRegion() {
		return region;
	}


	public void setRegion(String region) {
		this.region = region;
	}


	public long getCode_postal() {
		return code_postal;
	}


	public void setCode_postal(long code_postal) {
		this.code_postal = code_postal;
	}


	public long getId_adresse() {
		return id_adresse;
	}
}
