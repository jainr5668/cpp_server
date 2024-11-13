export class LoginModel{
    token:string;
    token_type: string;

    constructor(jsonData){
        this.token = jsonData['token'];
        this.token_type = jsonData['token_type'];
    }
}

export class LoginRequestModel{
    username: string;
    password: string;
  
    constructor(jsonData?: any) {
      if (typeof jsonData == 'object') {
        this.username = jsonData['username'];
        this.password = jsonData['password'];
      } else {
        this.username = '';
        this.password = '';
      }
    }
  }
  