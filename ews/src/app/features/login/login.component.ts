import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Observable } from 'rxjs';
import { StringIds, StringIdsType } from 'src/stringIds';
import { TranslateService } from '@ngx-translate/core';
import { LoginRequestModel } from './login.model';
import { CardModel } from '@patterns/card';
import { ContentModel } from '@patterns/content';
import { ElementModel } from '@patterns/element';
import { FooterModel, FooterTypeEnum } from '@patterns/footer';
import { ActivatedRoute, Router } from "@angular/router"
import { LoginService } from '@services/auth/login';
import { LoginModel } from '@services/auth/login';
import { AuthService } from '@utills/auth'

@Component({
  selector: 'feature-addUser',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
})
export class LoginComponent implements OnInit {
  // @Input() public homepage: LoginModel;

  @Output() clickListener = new EventEmitter();

  card: CardModel;

  loginmodel: LoginRequestModel = new LoginRequestModel();

  returnUrl: string;
  constructor(
    private translate: TranslateService,
    private loginService: LoginService,
    private router: Router,
    private authService: AuthService,
    private route: ActivatedRoute
  ) {
    this.route.queryParams.subscribe(params => {
      this.returnUrl = params['returnUrl'];
    });
  }

  ngOnInit(): void {
    this.generate_form();
  }

  generate_form() {
    let elements = [];
    let element = new ElementModel();

    // Username filed
    element.email('email', StringIds.cEMAIL, this.loginmodel, 'username');
    element.colspan = 1;
    elements.push(element);

    // Password field
    element = new ElementModel();
    element.passwordField('password', StringIds.cPASSWORD, this.loginmodel, 'password');
    element.colspan = 1;
    elements.push(element);

    // Creating content
    let content = new ContentModel();
    content.setContentValues('add-user-content', StringIds.cLOGIN);
    content.cols = 1;
    const footer = new FooterModel(
      FooterTypeEnum.APPLY_CANCEL,
      'add-user-footer',
      null,
      (event) => {
        this.submit(event);
      }
    );
    content.elements = elements;

    // Creating Card
    this.card = new CardModel();
    this.card.contents.push(content);
    this.card.footer = footer;
  }

  submit(event) {
    this.loginService.post(LoginModel, this.loginmodel).subscribe(
      {
        next: (response: LoginModel) => {
          this.authService.setToken(response.token);
          if (this.returnUrl) {
            this.router.navigate([this.returnUrl]);
          } else {
            this.router.navigate(['']);
          }
        },
        error: (error) => {

        }
      });
  };

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
}
