<?php

namespace Rector\Tests\TypeDeclaration\Rector\FunctionLike\ParamTypeDeclarationRector\Fixture;

final class LocalChildClass extends AbstractLocalParentClass
{
    /**
     * @param int $number
     */
    public function change($number)
    {
    }

    /**
     * @param int $number
     */
    public function changeToo($number)
    {
    }
}

abstract class AbstractLocalParentClass
{
    /**
     * @param int $number
     */
    public function changeToo($number)
    {
    }
}

?>
-----
<?php

namespace Rector\Tests\TypeDeclaration\Rector\FunctionLike\ParamTypeDeclarationRector\Fixture;

final class LocalChildClass extends AbstractLocalParentClass
{
    public function change(int $number)
    {
    }

    public function changeToo(int $number)
    {
    }
}

abstract class AbstractLocalParentClass
{
    public function changeToo(int $number)
    {
    }
}

?>
