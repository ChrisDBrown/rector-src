<?php

declare(strict_types=1);

namespace Rector\PhpSpecToPHPUnit;

use PhpParser\Node;
use PhpParser\Node\Expr\Variable;
use PhpParser\Node\Param;
use PhpParser\Node\Stmt\Class_;
use PhpParser\Node\Stmt\ClassMethod;
use Rector\Core\Exception\ShouldNotHappenException;
use Rector\Core\PhpParser\Node\BetterNodeFinder;
use Rector\NodeNameResolver\NodeNameResolver;
use Rector\NodeTypeResolver\Node\AttributeKey;
use Symplify\Astral\NodeTraverser\SimpleCallableNodeTraverser;

final class PhpSpecMockCollector
{
    /**
     * @var mixed[]
     */
    private array $mocks = [];

    /**
     * @var mixed[]
     */
    private array $mocksWithsTypes = [];

    /**
     * @var mixed[]
     */
    private array $propertyMocksByClass = [];

    public function __construct(
        private readonly SimpleCallableNodeTraverser $simpleCallableNodeTraverser,
        private readonly NodeNameResolver $nodeNameResolver,
        private readonly BetterNodeFinder $betterNodeFinder,
    ) {
    }

    /**
     * @return mixed[]
     */
    public function resolveClassMocksFromParam(Class_ $class): array
    {
        $className = (string) $this->nodeNameResolver->getName($class);

        if (isset($this->mocks[$className]) && $this->mocks[$className] !== []) {
            return $this->mocks[$className];
        }

        $this->simpleCallableNodeTraverser->traverseNodesWithCallable($class, function (Node $node) use ($class) {
            if (! $node instanceof ClassMethod) {
                return null;
            }

            if (! $node->isPublic()) {
                return null;
            }

            foreach ($node->params as $param) {
                $this->addMockFromParam($class, $param);
            }

            return null;
        });

        // set default value if none was found
        if (! isset($this->mocks[$className])) {
            $this->mocks[$className] = [];
        }

        return $this->mocks[$className];
    }

    public function isVariableMockInProperty(Class_ $class, Variable $variable): bool
    {
        $variableName = $this->nodeNameResolver->getName($variable);
        $className = (string) $this->nodeNameResolver->getName($class);

        return in_array($variableName, $this->propertyMocksByClass[$className] ?? [], true);
    }

    public function getTypeForClassAndVariable(Class_ $class, string $variable): string
    {
        $className = (string) $this->nodeNameResolver->getName($class);

        if (! isset($this->mocksWithsTypes[$className][$variable])) {
            throw new ShouldNotHappenException();
        }

        return $this->mocksWithsTypes[$className][$variable];
    }

    public function addPropertyMock(string $class, string $property): void
    {
        $this->propertyMocksByClass[$class][] = $property;
    }

    private function addMockFromParam(Class_ $class, Param $param): void
    {
        $variable = $this->nodeNameResolver->getName($param->var);

        $className = (string) $this->nodeNameResolver->getName($class);

        $classMethod = $this->betterNodeFinder->findParentType($param, ClassMethod::class);
        if (! $classMethod instanceof ClassMethod) {
            throw new ShouldNotHappenException();
        }

        $methodName = $this->nodeNameResolver->getName($classMethod);
        $this->mocks[$className][$variable][] = $methodName;

        if ($param->type === null) {
            throw new ShouldNotHappenException();
        }

        $paramType = (string) ($param->type ?? $param->type->getAttribute(AttributeKey::ORIGINAL_NAME));
        $this->mocksWithsTypes[$className][$variable] = $paramType;
    }
}
